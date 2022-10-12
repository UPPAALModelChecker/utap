SET(test_module "utap")

SET(extra_headers)

add_executable(pretty pretty.cpp)
target_link_libraries(pretty PRIVATE UTAP)

add_executable(syntaxcheck syntaxcheck.cpp)
target_link_libraries(syntaxcheck PRIVATE UTAP)

add_executable(taflow taflow.cpp)
target_link_libraries(taflow PRIVATE UTAP)

add_executable(featurecheck featurechecker.cpp external_fn.cpp)
target_link_libraries(featurecheck PRIVATE UTAP)

install(TARGETS pretty syntaxcheck taflow featurecheck)

if (TESTING)
    find_package(doctest REQUIRED)

    add_executable(test_expression test_expression.cpp)
    target_link_libraries(test_expression PRIVATE doctest::doctest UTAP)
    add_test(NAME test_expression COMMAND test_expression)

    add_library(external_fn SHARED external_fn.cpp)

    add_executable(test_parser test_parser.cpp)
    target_link_libraries(test_parser PRIVATE doctest::doctest UTAP)
    add_dependencies(test_parser external_fn)
    add_test(NAME test_parser COMMAND test_parser)

    add_executable(test_featurechecker test_featurechecker.cpp)
    target_link_libraries(test_featurechecker PRIVATE doctest::doctest UTAP)
    add_test(NAME test_featurechecker COMMAND test_featurechecker)

    add_executable(test_range test_range.cpp)
    target_link_libraries(test_range PRIVATE doctest::doctest UTAP)
    add_test(NAME test_range COMMAND test_range)


endif (TESTING)
