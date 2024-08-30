add_executable(pretty pretty.cpp)
target_link_libraries(pretty PRIVATE UTAP)

add_executable(syntaxcheck syntaxcheck.cpp)
target_link_libraries(syntaxcheck PRIVATE UTAP)

add_executable(featurecheck featurechecker.cpp)
target_link_libraries(featurecheck PRIVATE UTAP)

install(TARGETS pretty syntaxcheck featurecheck)

if(UTAP_WITH_TESTS)
  find_package(doctest REQUIRED)

  add_executable(expression_test expression_test.cpp)
  target_compile_definitions(expression_test
                             PRIVATE DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)
  target_link_libraries(expression_test PRIVATE UTAP doctest::doctest)
  add_test(NAME expression_test COMMAND expression_test)

  add_library(external_fn SHARED external_fn.cpp)

  add_executable(parser_test parser_test.cpp)
  target_compile_definitions(parser_test
                             PRIVATE DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)
  target_link_libraries(parser_test PRIVATE UTAP doctest::doctest)
  add_dependencies(parser_test external_fn)
  add_test(NAME parser_test COMMAND parser_test)

  add_executable(featurechecker_test featurechecker_test.cpp)
  target_compile_definitions(featurechecker_test
                             PRIVATE DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)
  target_link_libraries(featurechecker_test PRIVATE UTAP doctest::doctest)
  add_test(NAME featurechecker_test COMMAND featurechecker_test)

  add_executable(range_test range_test.cpp)
  target_compile_definitions(range_test
                             PRIVATE DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)
  target_link_libraries(range_test PRIVATE UTAP doctest::doctest)
  add_test(NAME range_test COMMAND range_test)

  add_executable(typechecker_test typechecker_test.cpp)
  target_compile_definitions(typechecker_test
                             PRIVATE DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)
  target_link_libraries(typechecker_test PRIVATE UTAP doctest::doctest)
  add_test(NAME typechecker_test COMMAND typechecker_test)

  add_executable(prettyprint_test prettyprint_test.cpp)
  target_compile_definitions(prettyprint_test
                             PRIVATE DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)
  target_link_libraries(prettyprint_test PRIVATE UTAP doctest::doctest)
  add_test(NAME prettyprint_test COMMAND prettyprint_test)

endif(UTAP_WITH_TESTS)
