cmake_minimum_required(VERSION 3.16)
project(UTAP VERSION 1.1.2 LANGUAGES CXX C)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

option(TESTING OFF)
option(STATIC OFF)
option(UBSAN OFF)
option(ASAN OFF)

cmake_policy(SET CMP0048 NEW) # project() command manages VERSION variables
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(UTAP_PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(UTAP_VERSION "${PACKAGE_VERSION}")
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${CMAKE_CURRENT_SOURCE_DIR}/libs")

add_compile_definitions(MODELS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/test/models")

find_package(FLEX 2.6.4 REQUIRED)
find_package(BISON 3.6.0 REQUIRED)
find_package(libxml2 2.9.14 REQUIRED)
#message(STATUS "Found LibXML2 ${LIBXML2_LIBRARIES}")
#message(STATUS "Using LIBXML2_INCLUDE_DIR=${LIBXML2_INCLUDE_DIR}")
#message(STATUS "Using LIBXML2_INCLUDE_DIRS=${LIBXML2_INCLUDE_DIRS}")
#message(STATUS "Using LIBXML2_LIBRARY=${LIBXML2_LIBRARY}")
#message(STATUS "Using LIBXML2_LIBRARIES=${LIBXML2_LIBRARIES}")
#message(STATUS "Using LIBXML2_DEFINITIONS=${LIBXML2_DEFINITIONS}")
add_definitions(${LIBXML2_DEFINITIONS})
if (TESTING)
    find_package(doctest 2.4.8 REQUIRED)
endif(TESTING)

# Create directory for the generated header files:
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/include/utap")

set(lexer_source "${CMAKE_CURRENT_BINARY_DIR}/lexer.cc")
add_custom_command(OUTPUT "${lexer_source}"
  COMMAND ${FLEX_EXECUTABLE} "--outfile=${lexer_source}" -Putap_ "${CMAKE_CURRENT_SOURCE_DIR}/src/lexer.l"
  DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/lexer.l"
)
add_custom_target(lexer_generate DEPENDS "${lexer_source}")

set(parser_source "${CMAKE_CURRENT_BINARY_DIR}/parser.cpp")
add_custom_command(OUTPUT "${parser_source}" "${CMAKE_CURRENT_BINARY_DIR}/include/parser.hpp"
    COMMAND ${BISON_EXECUTABLE} -putap_ -bparser "${CMAKE_CURRENT_SOURCE_DIR}/src/parser.y" "--output=${parser_source}" "--defines=${CMAKE_CURRENT_BINARY_DIR}/include/parser.hpp"
    DEPENDS lexer_generate "${CMAKE_CURRENT_SOURCE_DIR}/src/parser.y"
)
add_custom_target(parser_generate DEPENDS "${parser_source}")


FILE(GLOB utap_source "src/*.c" "src/*.cpp" "src/*.h")
add_library(UTAP ${utap_source} ${parser_source})
target_link_libraries(UTAP PRIVATE ${LIBXML2_LIBRARIES} ${CMAKE_DL_LIBS})

if (ASAN OR UBSAN)
    add_compile_options(-fno-omit-frame-pointer)
    add_link_options(-fno-omit-frame-pointer)
endif()
if (ASAN)
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
endif()
if (UBSAN)
    add_compile_options(-fsanitize=undefined)
    add_link_options(-fsanitize=undefined)
endif()

if(STATIC)
    set(CMAKE_CXX_STANDARD_LIBRARIES "-static -static-libgcc -static-libstdc++ ${CMAKE_CXX_STANDARD_LIBRARIES}")
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Werror=vla)
endif()

target_include_directories(UTAP
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_BINARY_DIR}/include
        ${LIBXML2_INCLUDE_DIRS}
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(TESTING)
    enable_testing()
    add_subdirectory("test")
endif(TESTING)

write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/UTAPConfigVersion.cmake VERSION ${PACKAGE_VERSION} COMPATIBILITY SameMajorVersion)

install(DIRECTORY include DESTINATION .)
install(TARGETS UTAP EXPORT UTAPConfig LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(EXPORT UTAPConfig DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/UTAP/)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/UTAPConfigVersion.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/UTAP )

# set(CMAKE_CXX_STANDARD_LIBRARIES "-static -lwsock32 -lws2_32 -lz -lmcfgthread ${CMAKE_CXX_STANDARD_LIBRARIES}")
