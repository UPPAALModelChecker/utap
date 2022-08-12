#!/usr/bin/env bash
set -e

if [ "$#" -lt 1 ]; then
    echo "Expecting a list of target platforms as arguments."
    echo "For example: ${BW}$0 linux64 win32${$NC}"
    echo "See ${BW}toolchain/*.cmake${NC} for the list of supported platforms."
fi

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LOCAL="$PROJECT_DIR/local"
BW="\e[1;97m" # bold white
NC="\e[0m"    # no color

for target in "$@" ; do
    BUILD="build-${target}-release"
    LIBS="${LOCAL}/${target}"
    "${PROJECT_DIR}/getlibs/getlibs.sh" "${target}"
    echo -e "${BW}${target}: Configuring UTAP${NC}"
    case $target in
	darwin*)
            CMAKE_EXTRA=-DSTATIC=OFF
            ;;
        win64)
            CMAKE_EXTRA=-DSTATIC=ON
            #cp $(x86_64-w64-mingw32-g++ --print-file-name=libwinpthread-1.dll) "$BUILD/test/"
            ;;
        win32)
            CMAKE_EXTRA=-DSTATIC=ON
            #cp $(i686-w64-mingw32-g++ --print-file-name=libwinpthread-1.dll) "$BUILD/test/"
            ;;
	*)
            CMAKE_EXTRA=-DSTATIC=ON
            ;;
    esac
    cmake -S . -B "$BUILD" -DCMAKE_TOOLCHAIN_FILE="$PROJECT_DIR/toolchain/${target}.cmake" -DCMAKE_PREFIX_PATH="$LIBS" -DCMAKE_INSTALL_PREFIX="$LIBS" -DCMAKE_BUILD_TYPE=Release -DTESTING=ON ${CMAKE_EXTRA}
    echo -e "${BW}${target}: Building UTAP${NC}"
    cmake --build "$BUILD"
    echo -e "${BW}${target}: Testing UTAP${NC}"
    (cd "$BUILD" ; ctest --output-on-failure)
    echo -e "${BW}Success!${NC}"
done
