# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

`libutap` (UTAP) is the Uppaal Timed Automata Parser — a C++17 library that parses and type-checks
Uppaal model files (`.xml`, `.xta`, `.ta` formats) into an in-memory AST (`Document`). It is a
dependency of the Uppaal model checker toolchain, licensed under LGPL.

## Build

Requires GCC 10+ (or compatible clang), Ninja or GNU make, CMake 3.16+ (presets need 3.28+),
`flex` >= 2.6.4, `bison` >= 3.6.0, and `libxml2` >= 2.6.10.

```shell
sudo apt-get install g++ ninja-build cmake flex bison libxml2-dev doctest-dev
```

Preferred workflow uses CMake presets (`CMakePresets.json` + `cmake/CommonPresets.json`):

```shell
cmake --workflow --preset default   # configure + build + test, Debug, single-config
cmake --workflow --preset debug     # multi-config Ninja, Debug
cmake --workflow --preset debug-san # Debug with ASan/UBSan/SSP
cmake --workflow --preset quick     # build only, no tests, no clang-tidy (fastest iteration)
```

Manual configure/build/test (no presets):

```shell
cmake . -B build -DCMAKE_INSTALL_PREFIX=$MYPATH -G Ninja
cmake --build build
ctest --test-dir build --output-on-failure
cmake --install build
```

Cross-compiling / full dependency bootstrap (fetches libxml2 etc. into `local/<target>`, then
configures, builds, tests, and installs):

```shell
./compile.sh x86_64-linux        # see cmake/toolchain/*.cmake for supported target names
```

Key CMake options (`CMakeLists.txt`): `UTAP_TESTS` (default ON), `UTAP_STATIC`, `UTAP_CLANG_TIDY`
(default ON — runs clang-tidy during the build), `UTAP_CCACHE` (default ON).

## Running tests

Tests use doctest and are registered individually with ctest (see `test/CMakeLists.txt`), so a
single test binary or case can be targeted directly:

```shell
ctest --test-dir build-multi --output-on-failure          # all tests
ctest --test-dir build-multi -R typechecker_test           # one test binary by ctest name
build-multi/Debug/typechecker_test --test-case="*scalar*"   # one doctest case, run binary directly
```

Test binaries: `expression_test`, `statement_test`, `parser_test`, `featurechecker_test`,
`range_test`, `typechecker_test`, `prettyprint_test`, `example_test`. Several depend on
`MODELS_DIR` (compiled in, points at `test/models/`) and `parser_test` additionally depends on the
`external_fn` shared library (built from `test/external_fn.cpp`) to exercise dynamically-loaded
functions.

## Coverage

`coverage-gcovr.sh` and `coverage-lcov.sh` configure/build/test the `coverage` preset (gcov) and
open an HTML report. `coverage-llvm.sh` does the same for the LLVM/clang coverage preset. All
regenerate their build dir (`build-coverage-gcov*`) from scratch via the preset.

## Code style

- `.clang-format` enforces formatting (Google-based, 4-space indent, 120 col) — run `clang-format`
  before committing.
- `.clang-tidy` enables a specific curated check set (readability/modernize/performance subset);
  `UTAP_CLANG_TIDY` runs it as part of the normal build.
- C++17, no compiler-specific extensions (`CMAKE_CXX_EXTENSIONS OFF`).

## Architecture

Information flow (see README.md section 5 for the original diagram):

```
.xml  --> libxml2 (SAX) --> xmlreader.cpp --\
                                              >--> bison parser (parser.y / lexer.l) --> ParserBuilder
.ta/.xta -----------------------------------/
```

- **Grammar**: `src/parser.y` (bison) and `src/lexer.l` (flex) implement the BNF for both old
  (3.x) and new (4.x) syntax, and are used both for direct `.ta`/`.xta` parsing and, reused
  block-by-block, for text embedded inside `.xml` documents. Generated parser/lexer land in the
  build directory (see `src/CMakeLists.txt` custom commands), not in source.
- **`ParserBuilder`** (`include/utap/builder.hpp`) is the abstract callback interface the grammar
  drives — one method per grammar production (types, declarations, statements, expressions,
  processes/templates, properties, LSC/SMC/priority extensions). The parser has no knowledge of
  how the model is stored; it only calls into whatever `ParserBuilder` implementation it's given.
- **Builder inheritance chain** turns those callbacks into an AST:
  `AbstractBuilder` (`ParserBuilder` + shared bookkeeping, e.g. type/name stacks)
  → `ExpressionBuilder` (expression trees)
  → `StatementBuilder` (statements)
  → `DocumentBuilder` (full `Document`: templates, processes, declarations).
  `PropertyBuilder`/`TigaPropertyBuilder` (`property.hpp`) similarly subclass `StatementBuilder`
  for query/property parsing. `PrettyPrinter` subclasses `AbstractBuilder` directly to regenerate
  source text from the same callback stream (used by the `pretty` tool and round-trip tests).
- **`Document`** (`include/utap/document.hpp`) is the resulting AST: templates, `Variable`,
  `Location`, `Edge`, `Branchpoint`, processes, and the system declaration. Symbols are `Symbol`
  objects (name + `Type`) grouped into `Frame`s representing scopes (`include/utap/symbols.hpp`).
  All expressions are `Expression` trees (`include/utap/expression.hpp`); all statements are
  `Statement` subclasses with a visitor hierarchy (`StatementVisitor` /
  `AbstractStatementVisitor` in `include/utap/statement.hpp`).
- **Post-parse passes** walk the built `Document` via `DocumentVisitor`/`AbstractStatementVisitor`:
  `TypeChecker` (`TypeChecker.cpp`, by far the largest source file) does the semantic type checking
  and rewriting after the whole document is built; `FeatureChecker` inspects which model features
  are in use (e.g. to pick symbolic/stochastic/concrete analysis support, see `SupportedMethods`).
- **`xmlreader.cpp`** bridges libxml2 SAX events to the bison parser for embedded expression/
  statement text inside XML elements; `xmlwriter.cpp` does the reverse (serializing a `Document`
  back to Uppaal XML).
- Public headers live under `include/utap/`; the top-level umbrella header is
  `include/utap/utap.hpp` (parse entry points operating on `Document&`, e.g. `parse_XML_file`,
  `parse_XTA`), while `include/utap/builder.hpp` exposes the lower-level entry points that operate
  directly on a `ParserBuilder&` instead of a `Document`.
- Command-line utilities built alongside the library (`src/CMakeLists.txt`): `pretty` (pretty-
  printer), `syntaxcheck`, `featurecheck` — thin executables over the corresponding builder/checker
  classes, useful for manually exercising a code path end-to-end against a real model file.

## Repo layout notes

- `examples/` is a self-contained consumer of the installed/built library, with its own CMake
  project and two build paths (`compile-with-getlibs.sh` vendors deps into `examples/local/`,
  `compile-with-cmake.sh` fetches deps via CMake) — useful as a template for exercising the public
  API in isolation from the main build.
- `cmake/toolchain/` holds CMake toolchain files for cross-compilation targets (Linux/macOS/mingw,
  multiple GCC/clang versions); `getlibs.sh` fetches and builds dependencies for a given target
  into `local/<target>`.
- CI matrix is defined across `.github/workflows/*.yml` (ubuntu-gcc, ubuntu-clang20, ubuntu-mingw,
  darwin-appleclang, darwin-brew-gcc15, nix).
