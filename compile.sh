#!/usr/bin/env bash
set -e

PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LOCAL="$PROJECT_DIR/local"
BW="\e[1;97m" # bold white
NC="\e[0m"    # no color

if [ "$#" -lt 1 ]; then
    echo "Expecting a list of target platforms as arguments."
    echo -e "For example: ${BW}$0 darwin linux64 win32${NC}"
    echo -e "See ${BW}cmake/toolchain/*.cmake${NC} for the list of supported platforms:"
    (cd cmake/toolchain ; ls)
fi

export CTEST_OUTPUT_ON_FAILURE=1

for target in "$@" ; do
    BUILD="build-${target}-release"
    if [ -d "${LOCAL}/${target}" ]; then
      PREFIX="-DCMAKE_PREFIX_PATH=${LOCAL}/${target}"
      INSTALL_PREFIX="-DCMAKE_INSTALL_PREFIX=${LOCAL}/${target}"
    else
      PREFIX=""
      INSTALL_PREFIX=""
    fi
    # "${PROJECT_DIR}/getlibs/getlibs.sh" "${target}"
    echo -e "${BW}${target}: Configuring UTAP${NC}"
    cmake -S . -B "$BUILD" -DCMAKE_TOOLCHAIN_FILE="$PROJECT_DIR/cmake/toolchain/${target}.cmake" \
      "${PREFIX}" "${INSTALL_PREFIX}" -DCMAKE_BUILD_TYPE=Release
    echo -e "${BW}${target}: Building UTAP${NC}"
    cmake --build "$BUILD"
    echo -e "${BW}${target}: Testing UTAP${NC}"
    (cd "$BUILD" ; ctest)
    echo -e "${BW}Success!${NC}"
done
