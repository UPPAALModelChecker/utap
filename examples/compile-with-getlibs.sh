#!/usr/bin/env bash
set -e
# Absolute path to the example directory:
EXAMPLE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# Path to UTAP library source directory:
[ -n "$UTAP_SRC" ] || UTAP_SRC=${EXAMPLE_DIR%/*}

# Figure out the native host target (architecture and kernel);
if [ -z "$TARGET" ] ; then
  ARCH=$(uname -m)
  KERNEL=$(uname -s)
  KERNEL=${KERNEL,,}
  TARGET="${ARCH}-${KERNEL}"
fi

# Where the dependent libraries are stored:
[ -n "$CMAKE_PREFIX_PATH" ] || export CMAKE_PREFIX_PATH="${EXAMPLE_DIR}/local/${TARGET}"
# Where to install the libraries:
[ -n "$CMAKE_INSTALL_PREFIX" ] || export CMAKE_INSTALL_PREFIX="${EXAMPLE_DIR}/local/${TARGET}"
# The build type:
[ -n "$CMAKE_BUILD_TYPE" ] || export CMAKE_BUILD_TYPE=Release
"${UTAP_SRC}/compile.sh" "$TARGET"

BUILD_DIR="${EXAMPLE_DIR}/build-${TARGET}-${CMAKE_BUILD_TYPE,,}"
cmake -B "$BUILD_DIR" -S "$EXAMPLE_DIR"
cmake --build "$BUILD_DIR"
ctest --test-dir "$BUILD_DIR" --output-on-failure
