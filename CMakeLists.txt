cmake_minimum_required(VERSION 3.16)
project(UTAP VERSION 1.0 LANGUAGES CXX C)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

option(TESTING OFF)
option(STATIC OFF)
option(UBSAN OFF)
option(ASAN OFF)

cmake_policy(SET CMP0048 NEW) # project() command manages VERSION variables
set(CMAKE_CXX_STANDARD 17)
set(UTAP_PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(UTAP_VERSION "${PACKAGE_VERSION}")

set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${CMAKE_CURRENT_SOURCE_DIR}/libs")

find_package(FLEX 2.6.4 REQUIRED)
find_package(BISON 3.0.4 REQUIRED)

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


FILE(GLOB utap_source "*.c" "*.cpp" "*.h")
add_library(UTAP ${utap_source} ${parser_source})
target_link_libraries(UTAP PRIVATE ${UTAP_SYSTEM_LIBRARIES} ${LIBXML2_LIBRARIES})


if (ASAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
endif()
if (UBSAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=undefined")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-omit-frame-pointer -fsanitize=undefined")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=undefined")
endif()

if(STATIC)
	set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
endif(STATIC)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Werror=vla)
endif()

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

include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

#if(TESTING)
#enable_testing()
#add_subdirectory("test")
#endif(TESTING)

write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/UTAPConfigVersion.cmake VERSION ${PACKAGE_VERSION} COMPATIBILITY SameMajorVersion)

install(DIRECTORY include DESTINATION .)
install(TARGETS UTAP EXPORT UTAPConfig LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(EXPORT UTAPConfig DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/UTAP/)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/UTAPConfigVersion.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/UTAP )
