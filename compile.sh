#!/usr/bin/env bash
set -e

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LOCAL="${PROJECT_DIR}/local"
BW="\e[1;97m" # bold white
NC="\e[0m"    # no color

if [ "$#" -lt 1 ]; then
    echo "Expecting a list of target platforms as arguments."
    echo -e "For example:"
    echo -e "    ${BW}$0 x86_64-linux${NC}"
    echo -e "List of supported platforms:"
    for toolchain in "${PROJECT_DIR}/cmake/toolchain"/*.cmake ; do
        platform=$(basename "$toolchain")
        echo -e "    ${BW}${platform%%.cmake}${NC}"
    done
fi

export CTEST_OUTPUT_ON_FAILURE=1

test -n "$CMAKE_BUILD_TYPE" || export CMAKE_BUILD_TYPE=Release

PREFIX="$CMAKE_PREFIX_PATH"
TOOLCHAIN_FILE="$CMAKE_TOOLCHAIN_FILE"
INSTALL_PREFIX="$CMAKE_INSTALL_PREFIX"

for target in "$@" ; do
    case "$target" in
        win64*|x86_64-w64-mingw32*)
            export WINARCH=win64
            export WINEPATH=$("${PROJECT_DIR}/winepath-for" x86_64-w64-mingw32)
            export CROSSCOMPILING_EMULATOR=wine
            ;;
        win32*|i686-w64-mingw32*)
            export WINARCH=win32
            export WINEPATH=$("${PROJECT_DIR}/winepath-for" i686-w64-mingw32)
            export CROSSCOMPILING_EMULATOR=wine
            ;;
        *)
            unset WINARCH
            unset WINEPATH
    esac
    if [ -n "$TOOLCHAIN_FILE" ]; then
        export CMAKE_TOOLCHAIN_FILE="$TOOLCHAIN_FILE"
    elif [ -r "${PROJECT_DIR}/cmake/toolchain/${target}.cmake" ]; then
        export CMAKE_TOOLCHAIN_FILE="${PROJECT_DIR}/cmake/toolchain/${target}.cmake"
    else
        unset CMAKE_TOOLCHAIN_FILE
    fi
    "${PROJECT_DIR}/getlibs.sh" "${target}"
    if [ -n "$PREFIX" ]; then
        export CMAKE_PREFIX_PATH="$PREFIX"
    elif [ -d "${LOCAL}/${target}" ]; then
        export CMAKE_PREFIX_PATH="${LOCAL}/${target}"
    else
        unset CMAKE_PREFIX_PATH
    fi
    if [ -n "$INSTALL_PREFIX" ]; then
        export CMAKE_INSTALL_PREFIX="$INSTALL_PREFIX"
    elif [ -d "${LOCAL}/${target}" ]; then
        export CMAKE_INSTALL_PREFIX="${LOCAL}/${target}"
    else
        unset CMAKE_INSTALL_PREFIX
    fi
    BUILD="build-${target}-release"
    echo -e "${BW}${target}: Configuring UTAP:${NC}"
    echo "    CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE:-(unset)}"
    echo "    CMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE:-(unset)}"
    echo "    CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH:-(unset)}"
    echo "    CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX:-(unset)}"
    cmake -B "$BUILD" -DCMAKE_INSTALL_PREFIX="$INSTALL_PREFIX"
    echo -e "${BW}${target}: Building UTAP${NC}"
    cmake --build "$BUILD" --config "$CMAKE_BUILD_TYPE"
    echo -e "${BW}${target}: Testing UTAP${NC}"
    echo "    WINEPATH=${WINEPATH:-(unset)}"
    echo "    WINARCH=${WINARCH:-(unset)}"
    ctest --test-dir "$BUILD" -C "$CMAKE_BUILD_TYPE"
    echo "Run the following to install UTAP into $CMAKE_INSTALL_PREFIX:"
    echo "    cmake --install \"$BUILD\" --config $CMAKE_BUILD_TYPE --prefix \"$CMAKE_INSTALL_PREFIX\""
    echo -e "${BW}$target: Success!${NC}"
done
