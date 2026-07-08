#!/usr/bin/env bash
set -e

BUILD_DIR=build-coverage-gcov
COVERAGE_INFO="${BUILD_DIR}/coverage.info"
COVERAGE_DIR="${BUILD_DIR}/coverage_report"

cmake --preset coverage
cmake --build --preset coverage
lcov --zerocounters --directory "$BUILD_DIR"
ctest --preset coverage
lcov --capture --directory "$BUILD_DIR" --output-file "$COVERAGE_INFO"
lcov --remove "$COVERAGE_INFO" '/usr/*' --output-file "$COVERAGE_INFO"
genhtml "$COVERAGE_INFO" --output-directory "$COVERAGE_DIR"
xdg-open "$COVERAGE_DIR/index.html"
