#!/usr/bin/env bash
set -e

BUILD_DIR=build-coverage-llvm
COVERAGE_DIR="${BUILD_DIR}/coverage_report"
PROFDATA="${BUILD_DIR}/coverage.profdata"

mkdir -p "$COVERAGE_DIR"

cmake -DCMAKE_TOOLCHAIN_FILE=$PWD/cmake/toolchain/x86_64-linux-clang.cmake --preset coverage-llvm
cmake --build --preset coverage-llvm

# each test binary gets its own raw profile (keyed by pid), otherwise they clobber
# one another since they'd all default to writing "default.profraw"
rm -f "$BUILD_DIR"/test/coverage-*.profraw
LLVM_PROFILE_FILE="$PWD/$BUILD_DIR/test/coverage-%p.profraw" ctest --preset coverage-llvm

llvm-profdata merge -sparse "$BUILD_DIR"/test/coverage-*.profraw -o "$PROFDATA"

# only target_coverage()-linked binaries (e.g. libUTAP.so) carry the __llvm_covmap
# section; the test executables themselves are not instrumented, so discover the
# actual instrumented binaries instead of assuming which ones they are
mapfile -t OBJECTS < <(
    find "$BUILD_DIR" -path "$BUILD_DIR/_deps" -prune -o \
        -type f \( -executable -o -name "*.so*" \) -print |
    while read -r f; do
        readelf -S "$f" 2>/dev/null | grep -q __llvm_covmap && echo "$f"
    done
)
OBJECT_ARGS=()
for obj in "${OBJECTS[@]:1}"; do
    OBJECT_ARGS+=(-object "$obj")
done

llvm-cov show "${OBJECTS[0]}" "${OBJECT_ARGS[@]}" \
    -instr-profile="$PROFDATA" \
    -format=html -output-dir="$COVERAGE_DIR" \
    -show-mcdc -show-branches=count \
    -ignore-filename-regex='(_deps|/test/)/'
xdg-open "$COVERAGE_DIR/index.html"
