cmake_minimum_required(VERSION 3.16)
project(UTAP VERSION 2.0.2 LANGUAGES CXX C)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  # top level project: most likely development, thus enable tests
  set(UTAP_WITH_TESTS_DEFAULT ON)
else()
  # the library is included into another project, no need for tests
  set(UTAP_WITH_TESTS_DEFAULT OFF)
endif()

if(WIN32)
  set(UTAP_STATIC_DEFAULT ON)
  set(BUILD_SHARED_LIBS OFF)
  add_compile_definitions(LIBXML_STATIC) # probably an issue with LibXml2 exports
else(WIN32)
  set(UTAP_STATIC_DEFAULT OFF)
endif(WIN32)

option(UTAP_WITH_TESTS "UTAP Unit Tests" ${UTAP_WITH_TESTS_DEFAULT})
option(UTAP_STATIC "UTAP Static Linking" ${UTAP_STATIC_DEFAULT})

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
    #set(CMAKE_CXX_STANDARD_LIBRARIES "-static -static-libgcc -static-libstdc++ ${CMAKE_CXX_STANDARD_LIBRARIES}")
    set(CMAKE_EXE_LINKER_FLAGS -static)
    message(STATUS "Enabled STATIC linking")
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
