SET(test_module "utap")

add_definitions("-DSYSTEMS_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/systems\"")

SET(extra_headers)

add_executable(pretty pretty.cpp)
target_link_libraries(pretty UTAP)

add_executable(syntaxcheck syntaxcheck.cpp)
target_link_libraries(syntaxcheck UTAP)

add_executable(taflow taflow.cpp)
target_link_libraries(taflow UTAP)

add_executable(featurecheck featurechecker.cpp)
target_link_libraries(featurecheck UTAP)

if (TESTING)
    find_package(Boost 1.71.0 REQUIRED COMPONENTS unit_test_framework REQUIRED)
    add_executable(test_parser test_parser.cpp test_featurechecker.cpp test_range.cpp)
    target_link_libraries(test_parser PRIVATE Boost::unit_test_framework UTAP)
    add_test(NAME test_parser COMMAND test_parser)
endif (TESTING)
