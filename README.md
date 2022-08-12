# libutap, version 0.94

# Mini HOWTO
Gerd Behrmann

Marius Mikučionis

1. What is libutap
2. Compiling
3. Simple use
4. Parsing trace files
5. Architecture
6. Issues

## 1. What is libutap

libutap is the Uppaal Timed Automata Parser. Uppaal is an integrated
tool environment for designing, simulating and verifying real time
systems modeled as extended timed automata. `libutap` is the parser for
Uppaal documents.

libutap has the ability to parse and type check Uppaal models in any
of the three file formats supported by Uppaal.

libutap is licensed under the LGPL.

## 2. Compiling

Use `cmake` to compile `libutap` easily for various platforms. 
You will need GCC version 10 or newer, Ninja or GNU make,
and `libxml2` from [XMLSoft](https://www.xmlsoft.org) (at least version 2.6.10).

Run the following to compile libutap and use it in the build:

```sh
sudo apt-get install bison cmake ninja-build flex libxml2-dev g++
cmake . -B build # -DCMAKE_INSTALL_PREFIX=$MYPATH # to install to $MYPATH
cmake --build build
```

Run the following to install libutap:
```
cmake --install build
```

Test:
```sh
ctest --test-dir build
```

For other platforms please see [compile.sh](compile.sh) script:
```sh
./compile.sh [linux64] [win64] [linux32] [win32] [darwin] 
```
`win64` requires `x86_64-w64-mingw32-g++` from [MinGW-w64](https://www.mingw-w64.org/) (either from Linux distribution or [MSYS2](https://www.msys2.org/)).

`win32` requires `i686-w64-mingw32-g++` from [MinGW-w64](https://www.mingw-w64.org/) (either from Linux distribution or [MSYS2](https://www.msys2.org/)).

`linux32` requires `g++-multilib`. 

`darwin` requires [gcc-10](https://formulae.brew.sh/formula/gcc@10) with [XCode](https://developer.apple.com/xcode/) installed.

## 3. Simple use

There are two ways one can use the library. In its simplest form, one
calls one of the top level parsing functions defined in [utap/utap.h](src/utap/utap.h),
e.g. `example.cpp`:

```cpp
#include <stdio.h>
#include "utap/utap.h"

int main()
{
  UTAP::TimedAutomataSystem system;
  parseXMLFile("myfile.xml", &system, true);
}
```

The first argument is the file to read. The second is the output of
the parser and the third is a flag indicating whether we want to use
the new or the old syntax (the old syntax is the one used in Uppaal
3.4, the new is the one that will be used since Uppaal 3.6).

After the call to `parseXMLFile`, one can access the network of timed
automata in the system variable. Take a look at [utap/system.h](src/utap/system.h) to see
what kind of structures you can access.
Distribution also includes [pretty.cpp](src/pretty.cpp) for pretty-printing model files.
See also doxygen API documentation in [doc/api/index.html](doc/api/index.html).

Use the following command to compile the example:

```sh
g++ example.cpp -o example -lutap -lxml2
```

If UTAP was configured with `-DCMAKE_INSTALL_PREFIX=$MYPATH` to install in custom location
then use the following to compile:

```sh
g++ -I$MYPATH/include example.cpp -o example -L$MYPATH/lib -lutap -lxml2
```

## 4. Parsing Uppaal Trace Files

`verifyta` utility from Uppaal distribution (`bin-*` folder) is able to print traces in human readable format (see `verifyta -h` and in particular keys `-t` and `-f`, also `-X` can produce `xml`).

If a custom format or some kind of transformation is needed, UTAP includes `tracer` utility which can parse and print trace files in human readable form. The source is included, thus the output can be modified accordingly.

First, `tracer` needs an `.if` file -- an intermediate format representation of the same model that was used to produce the trace. The `.if` file is produced by `verifyta` utility from Uppaal distribution:
```sh
UPPAAL_COMPILE_ONLY=1 verifyta model.xml > model.if
```
Then `tracer` can be applied as follows:
```sh
tracer model.if trace.xtr
```

## 5. Architecture

The following ASCII figure shows the initial information flow through
the library.

<pre>
 +----\
 |    |\
 |    +-\
 |      |   --> libxml2 --[SAX-interface]--> "xmlreader.cc"
 | .xml |                                         |
 |      |                                         |
 +------+                                         |
                                                  |
 +----\                                           |
 |    |\                                          |
 |    +-\                                         v
 | .ta  |                            +--------------------------+
 | .xta |   -----------------------> | bison parser (parser.yy) |
 |      |                            +--------------------------+
 +------+                                           |
                                                    |
 +------+                                           |
 |      |                                           |
 | TAS  |                                           |
 |      |      +---------------+                    |
 |      | <--- | SystemBuilder |<--[ParserBuilder]--/
 |      |      +---------------+
 +------+
</pre>

The BNF implemented by the bison generated parser is split into
several sections and to some extend duplicated for the old and new
syntax. It can read `.ta` and `.xta` files directly. `XML` files are read
using the `libxml2` library. Each text-block in the `XML` file is then
parser wrt. the BNF for that block (see [xmlreader.cpp](src/xmlreader.cpp)). For this, the
`bison` generated parser is reused.

The parser calls methods in the abstract `ParserBuilder` class. The
methods in the `ParserBuilder` class are implemented by the
SystemBuilder class which is a subclass of ExpressionBuilder which is
a subclass of `AbstractBuilder`. The `SystemBuilder` writes the model to
an instance of the `TimedAutomataSystem` (TAS) class.

The design abstracts the differences between the `.xml`, `.xta` and `.ta`
input formats and also hides the differences between the 3.4 and
3.6/4.0 formats from any implementation of the `ParserBuilder` interface
(for equivalent input the parser will call the same methods in the
ParserBuilder class).

A TAS object represents the templates, variables, locations,
transitions and processes of a model. Symbols are represented by
`symbol_t` objects (see the API documentation). A symbol is a name (a
string) with a type. The type is represented by a `type_t`
object. Symbols are grouped into frames (represented by `frame_t`
objects). Frames are used to represent scopes and other collections of
symbols such as records or parameters of templates and functions.

All expressions are represented using a tree structure where the
leaves represent values or variables and the inner nodes represent
operations. Each node is referenced using an `expression_t` object.

## 6. Issues

Please use the [Issues](https://github.com/UPPAALModelChecker/utap/issues) tab at the top to report problems.
