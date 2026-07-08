#!/usr/bin/env bash
set -e

BUILD_DIR=build-coverage-gcov
COVERAGE_DIR="${BUILD_DIR}/coverage_report"

mkdir -p "$COVERAGE_DIR"

cmake --preset coverage
cmake --build --preset coverage
ctest --preset coverage
gcovr --root . "$BUILD_DIR" --html --html-details -o "$COVERAGE_DIR/index.html"
xdg-open "$COVERAGE_DIR/index.html"
