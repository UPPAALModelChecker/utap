#!/usr/bin/env bash
set -e

if [ "$#" -lt 1 ]; then
    echo "Expecting a list of target platforms as arguments."
    echo "For example: ${BW}$0 linux64 win32${$NC}"
    echo "See ${BW}toolchain/*.cmake${NC} for the list of supported platforms."
fi

GETLIBS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR=$(dirname "$GETLIBS_DIR")
source "$GETLIBS_DIR/sources.sh"

for target in "$@" ; do
    LIBS="$LOCAL/$target"
    # libxml2
    if [ ! -r "$LIBS/lib/libxml2.a" ] ; then
        echo -e "${BW}Preparing source of ${LIBXML2}${NC}"
        prepare_libxml2
        BUILD="$LIBS/build-${LIBXML2}"
        echo -e "${BW}${target}: Configuring ${LIBXML2}${NC}"
        cmake -S "$SOURCE/$LIBXML2" -B "$BUILD" -DCMAKE_TOOLCHAIN_FILE="$PROJECT_DIR/toolchain/${target}.cmake" \
          -DCMAKE_PREFIX_PATH="$LIBS" -DCMAKE_INSTALL_PREFIX="$LIBS" -DCMAKE_BUILD_TYPE=Release \
          -DBUILD_SHARED_LIBS=OFF -DLIBXML2_WITH_ICONV=OFF -DLIBXML2_WITH_LZMA=OFF -DLIBXML2_WITH_PYTHON=OFF -DLIBXML2_WITH_ZLIB=OFF
        echo -e "${BW}${target}: Building ${LIBXML2}${NC}"
        cmake --build "$BUILD"
        echo -e "${BW}${target}: Testing ${LIBXML2}${NC}"
        case "$target" in
            win64)
                cp $(x86_64-w64-mingw32-g++ --print-file-name=libwinpthread-1.dll) "$BUILD/"
                ;;
            win32)
                cp $(i686-w64-mingw32-g++ --print-file-name=libwinpthread-1.dll) "$BUILD/"
                ;;
        esac
        (cd "$BUILD" ; ctest --output-on-failure)
        echo -e "${BW}${target}: Installing ${LIBXML2}${NC}"
        cmake --install "$BUILD"
        rm -Rf "$BUILD"
        echo -e "${BW}${target}: Success ${LIBXML2}${NC}"
    else
        echo -e "${BW}${target}: ${LIBXML2} is already installed.${NC}"
    fi
    if [ ! -r "$LIBS/include/doctest/doctest.h" ] ; then
        echo -e "${BW}Preparing source of ${DOCTEST}${NC}"
        prepare_doctest
        BUILD="$LIBS/build-${DOCTEST}"
        echo -e "${BW}${target}: Configuring ${DOCTEST}${NC}"
        cmake -S "$SOURCE/$DOCTEST" -B "$BUILD" -DCMAKE_TOOLCHAIN_FILE="$PROJECT_DIR/toolchain/${target}.cmake" \
          -DCMAKE_PREFIX_PATH="$LIBS" -DCMAKE_INSTALL_PREFIX="$LIBS" -DCMAKE_BUILD_TYPE=Release
        echo -e "${BW}${target}: Building ${DOCTEST}${NC}"
        cmake --build "$BUILD"
        #echo -e "${BW}${target}: Testing ${DOCTEST}${NC}"
        #(cd "$BUILD" ; ctest --output-on-failure)
        echo -e "${BW}${target}: Installing ${DOCTEST}${NC}"
        cmake --install "$BUILD"
        rm -Rf "$BUILD"
        echo -e "${BW}${target}: Success ${DOCTEST}${NC}"
    else
        echo -e "${BW}${target}: ${DOCTEST} is already installed.${NC}"
    fi
done
