#!/usr/bin/env bash
set -e

GETLIBS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR=$(dirname "$GETLIBS_DIR")
LOCAL="$PROJECT_DIR/local"
SOURCE="$LOCAL/source"
BW="\e[1;97m" # bold white
NC="\e[0m"    # no color

LIBXML2=libxml2-2.9.14
LIBXML2_Z="${LIBXML2}.tar.xz"
LIBXML2_URL="https://people.cs.aau.dk/~marius/mirrors/libxml2/${LIBXML2_Z}"
LIBXML2_SHA256=60d74a257d1ccec0475e749cba2f21559e48139efba6ff28224357c7c798dfee

DOCTEST=doctest-2.4.9
DOCTEST_Z=${DOCTEST}.tar.gz
DOCTEST_URL="https://github.com/doctest/doctest/archive/refs/tags/v${DOCTEST#doctest-}.tar.gz"
DOCTEST_SHA256=19b2df757f2f3703a5e63cee553d85596875f06d91a3333acd80a969ef210856

function download_unpack {
    local LIB="${1}"
    local LIB_URL="${LIB}_URL"
    local LIB_SUM="${LIB}_SHA256"
    local LIB_Z="${LIB}_Z"
    mkdir -p "$SOURCE"
    pushd "$SOURCE"
    if [ ! -r "${!LIB_Z}" ]; then
        echo -e "${BW}Downloading ${!LIB_Z}${NC}"
        wget -nv "${!LIB_URL}" -O "${!LIB_Z}" || { echo "Download failed"; exit 1; }
    fi
    echo "${!LIB_SUM}" "${!LIB_Z}" | sha256sum --check || \
        { echo "  expected: ${!LIB_SUM}"; echo "  got     : $(sha256sum "${!LIB_Z}")"; exit 2; }
    if [ ! -d "${!LIB}" ]; then
        echo -e "${BW}Extracting ${!LIB}${NC}"
        case "${!LIB_Z}" in
            *.7z)
                7z x -aoa "${!LIB_Z}"
                ;;
            *.tar.*)
                tar xf "${!LIB_Z}"
                ;;
            *)
                echo "Don't know how to extract $${!LIB_Z}"
        esac
    fi
    popd
}

function prepare_libxml2 {
    download_unpack LIBXML2
}

function prepare_doctest {
    download_unpack DOCTEST
}
