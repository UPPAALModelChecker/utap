set(MODELS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/models")
set(EXAMPLES_PATH "${PROJECT_SOURCE_DIR}/examples")

add_executable(abstractbuilder_test AbstractBuilder_test.cpp)
target_link_libraries(abstractbuilder_test PRIVATE UTAP doctest::doctest_with_main)
add_test(NAME abstractbuilder_test COMMAND abstractbuilder_test)

add_executable(expression_test expression_test.cpp)
target_link_libraries(expression_test PRIVATE UTAP doctest::doctest_with_main)
add_test(NAME expression_test COMMAND expression_test)

add_executable(statement_test statement_test.cpp)
target_link_libraries(statement_test PRIVATE UTAP doctest::doctest_with_main)
add_test(NAME statement_test COMMAND statement_test)

add_library(external_fn SHARED external_fn.cpp)
target_compile_features(external_fn PUBLIC cxx_std_11)

add_executable(parser_test parser_test.cpp)
target_compile_definitions(parser_test PRIVATE MODELS_DIR="${MODELS_PATH}")
target_link_libraries(parser_test PRIVATE UTAP doctest::doctest_with_main)
add_dependencies(parser_test external_fn)
add_test(NAME parser_test COMMAND parser_test WORKING_DIRECTORY $<TARGET_FILE_DIR:parser_test>)

add_executable(featurechecker_test featurechecker_test.cpp)
target_compile_definitions(featurechecker_test PRIVATE MODELS_DIR="${MODELS_PATH}")
target_link_libraries(featurechecker_test PRIVATE UTAP
                                                  doctest::doctest_with_main)
add_test(NAME featurechecker_test COMMAND featurechecker_test)

add_executable(range_test range_test.cpp)
target_link_libraries(range_test PRIVATE UTAP doctest::doctest_with_main)
add_test(NAME range_test COMMAND range_test)

add_executable(typechecker_test typechecker_test.cpp)
target_compile_definitions(
  typechecker_test PRIVATE MODELS_DIR="${MODELS_PATH}")
target_link_libraries(typechecker_test PRIVATE UTAP doctest::doctest_with_main)
add_test(NAME typechecker_test COMMAND typechecker_test)

add_executable(prettyprint_test prettyprint_test.cpp)
target_compile_definitions(
  prettyprint_test PRIVATE MODELS_DIR="${MODELS_PATH}")
target_link_libraries(prettyprint_test PRIVATE UTAP doctest::doctest_with_main)
add_test(NAME prettyprint_test COMMAND prettyprint_test)

add_executable(prettyprinter_test PrettyPrinter_test.cpp)
target_compile_definitions(
  prettyprinter_test PRIVATE MODELS_DIR="${MODELS_PATH}")
target_link_libraries(prettyprinter_test PRIVATE UTAP doctest::doctest_with_main)
add_test(NAME prettyprinter_test COMMAND prettyprinter_test)

add_executable(typeexception_test typeexception_test.cpp)
target_link_libraries(typeexception_test PRIVATE UTAP doctest::doctest_with_main)
add_test(NAME typeexception_test COMMAND typeexception_test)

add_executable(print_test print_test.cpp)
target_include_directories(print_test PRIVATE "${PROJECT_SOURCE_DIR}/src")
target_link_libraries(print_test PRIVATE UTAP doctest::doctest_with_main)
# print.hpp is header-only, so its templates are instantiated directly in
# this test binary rather than inside the already-instrumented UTAP library;
# it needs its own coverage instrumentation to be measured.
target_coverage(print_test)
add_test(NAME print_test COMMAND print_test)

add_executable(property_test property_test.cpp)
target_compile_definitions(property_test PRIVATE MODELS_DIR="${MODELS_PATH}")
target_link_libraries(property_test PRIVATE UTAP doctest::doctest_with_main)
add_test(NAME property_test COMMAND property_test)

add_executable(example_test example_test.cpp)
target_link_libraries(example_test PRIVATE UTAP)
add_test(NAME example_train_gate
         COMMAND example_test "${EXAMPLES_PATH}/train-gate.xml"
                 "${EXAMPLES_PATH}/train-gate-out.xml")

if(UTAP_STATIC)
  target_link_options(abstractbuilder_test PRIVATE -static)
  target_link_options(expression_test PRIVATE -static)
  target_link_options(statement_test PRIVATE -static)
  target_link_options(parser_test PRIVATE -static)
  target_link_options(featurechecker_test PRIVATE -static)
  target_link_options(range_test PRIVATE -static)
  target_link_options(typechecker_test PRIVATE -static)
  target_link_options(prettyprint_test PRIVATE -static)
  target_link_options(prettyprinter_test PRIVATE -static)
  target_link_options(typeexception_test PRIVATE -static)
  target_link_options(print_test PRIVATE -static)
  target_link_options(property_test PRIVATE -static)
  target_link_options(example_test PRIVATE -static)
  message(STATUS "Enabled Unit Tests -static")
endif(UTAP_STATIC)
