#!/usr/bin/env bash
set -e

GETLIBS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR=$(dirname "$GETLIBS_DIR")
LOCAL="$PROJECT_DIR/local"
SOURCE="$LOCAL/source"
BW="\e[1;97m" # bold white
NC="\e[0m"    # no color

LIBXML2=libxml2-2.11.5
LIBXML2_Z="${LIBXML2}.tar.xz"
LIBXML2_URL="https://people.cs.aau.dk/~marius/mirrors/libxml2/${LIBXML2_Z}"
LIBXML2_SHA256=3727b078c360ec69fa869de14bd6f75d7ee8d36987b071e6928d4720a28df3a6

DOCTEST=doctest-2.4.11
DOCTEST_Z="${DOCTEST}.tar.gz"
DOCTEST_URL="https://github.com/doctest/doctest/archive/refs/tags/v${DOCTEST#doctest-}.tar.gz"
DOCTEST_SHA256=632ed2c05a7f53fa961381497bf8069093f0d6628c5f26286161fbd32a560186

BISON=bison-3.8.2
BISON_Z="${BISON}.tar.gz"
BISON_URL="https://ftp.gnu.org/gnu/bison/${BISON_Z}"
BISON_SHA256=06c9e13bdf7eb24d4ceb6b59205a4f67c2c7e7213119644430fe82fbd14a0abb

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
                echo "Don't know how to extract ${!LIB_Z}"
                exit 1
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

function prepare_bison {
    download_unpack BISON
}
