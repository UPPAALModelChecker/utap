cmake_minimum_required(VERSION 3.16)
project(UTAP VERSION 1.1.6 LANGUAGES CXX C)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

option(UTAP_WITH_TESTS "UTAP Unit Tests" PROJECT_IS_TOP_LEVEL)
option(UTAP_STATIC "UTAP Static Linking" OFF)

cmake_policy(SET CMP0048 NEW) # project() command manages VERSION variables
include(cmake/stdcpp.cmake)
include(cmake/sanitizers.cmake)

set(UTAP_PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(UTAP_VERSION "${PACKAGE_VERSION}")
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${CMAKE_CURRENT_SOURCE_DIR}/libs")

add_compile_definitions(MODELS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test/models")

find_package(FLEX 2.6.4 REQUIRED)
find_package(BISON 3.6.0 REQUIRED)
include(cmake/libxml2.cmake)

if(UTAP_STATIC)
    set(CMAKE_CXX_STANDARD_LIBRARIES "-static -static-libgcc -static-libstdc++ ${CMAKE_CXX_STANDARD_LIBRARIES}")
endif(UTAP_STATIC)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Werror=vla)
endif()

add_subdirectory(src)

if (UTAP_WITH_TESTS)
    include(cmake/doctest.cmake)
    enable_testing()
endif(UTAP_WITH_TESTS)
add_subdirectory(test)

target_include_directories(UTAP
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_BINARY_DIR}/include
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/UTAPConfigVersion.cmake VERSION ${PACKAGE_VERSION} COMPATIBILITY SameMajorVersion)

install(DIRECTORY include DESTINATION .)
install(TARGETS UTAP EXPORT UTAPConfig LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(EXPORT UTAPConfig DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/UTAP/)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/UTAPConfigVersion.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/UTAP )

# set(CMAKE_CXX_STANDARD_LIBRARIES "-static -lwsock32 -lws2_32 -lz -lmcfgthread ${CMAKE_CXX_STANDARD_LIBRARIES}")
