SET(test_module "utap")

SET(extra_headers)

add_executable(pretty pretty.cpp)
target_link_libraries(pretty PRIVATE UTAP)

add_executable(syntaxcheck syntaxcheck.cpp)
target_link_libraries(syntaxcheck PRIVATE UTAP)

add_executable(taflow taflow.cpp)
target_link_libraries(taflow PRIVATE UTAP)

add_executable(featurecheck featurechecker.cpp)
target_link_libraries(featurecheck PRIVATE UTAP)

install(TARGETS pretty syntaxcheck taflow featurecheck)

if (UTAP_WITH_TESTS)
    find_package(doctest REQUIRED)

    add_executable(test_expression test_expression.cpp)
    target_link_libraries(test_expression PRIVATE UTAP doctest::doctest_with_main)
    add_test(NAME test_expression COMMAND test_expression)

    add_library(external_fn SHARED external_fn.cpp)

    add_executable(test_parser test_parser.cpp)
    target_link_libraries(test_parser PRIVATE UTAP doctest::doctest_with_main)
    add_dependencies(test_parser external_fn)
    add_test(NAME test_parser COMMAND test_parser)

    add_executable(test_featurechecker test_featurechecker.cpp)
    target_link_libraries(test_featurechecker PRIVATE UTAP doctest::doctest_with_main)
    add_test(NAME test_featurechecker COMMAND test_featurechecker)

    add_executable(test_range test_range.cpp)
    target_link_libraries(test_range PRIVATE UTAP doctest::doctest_with_main)
    add_test(NAME test_range COMMAND test_range)

    add_executable(test_typechecker test_typechecker.cpp)
    target_link_libraries(test_typechecker PRIVATE UTAP doctest::doctest_with_main)
    add_test(NAME test_typechecker COMMAND test_typechecker)

endif(UTAP_WITH_TESTS)
