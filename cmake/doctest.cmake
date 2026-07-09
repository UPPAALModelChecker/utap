# Downloads and compiles DocTest unit testing framework
include(FetchContent)
#set(FETCHCONTENT_QUIET ON)
#set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

FetchContent_Declare(doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.5.3    # "main" for latest
        GIT_SHALLOW TRUE  # download specific revision only (git clone --depth 1)
        GIT_PROGRESS TRUE # show download progress in Ninja
        EXCLUDE_FROM_ALL ON # don't build if not used
        FIND_PACKAGE_ARGS 2.5.3)

set(DOCTEST_WITH_TESTS OFF CACHE BOOL "Build tests/examples")
set(DOCTEST_WITH_MAIN_IN_STATIC_LIB ON CACHE BOOL "Build a static lib for doctest::doctest_with_main")
set(DOCTEST_NO_INSTALL OFF CACHE BOOL "Skip the installation process")
set(DOCTEST_USE_STD_HEADERS OFF CACHE BOOL "Use std headers")

FetchContent_MakeAvailable(doctest)

if(doctest_FOUND) # find_package
    message(STATUS "Found doctest: ${doctest_DIR}")
else(doctest_FOUND) # FetchContent
    message(STATUS "Fetched doctest: ${doctest_SOURCE_DIR}")
endif(doctest_FOUND)

if (TARGET doctest::doctest)
    message(STATUS "    Available target: doctest::doctest")
else()
    message(FATAL_ERROR "    Target not found: doctest::doctest")
endif ()

if (TARGET doctest::doctest_with_main)
  message(STATUS "    Available target: doctest::doctest_with_main")
  if (TARGET doctest_with_main)
    message(STATUS "    Available target: doctest_with_main")
  else ()
    add_library(doctest_with_main INTERFACE)
    target_link_libraries(doctest_with_main INTERFACE doctest::doctest_with_main)
    message(STATUS "    Created   target: doctest_with_main")
  endif()
else()
  add_library(doctest_with_main INTERFACE)
  target_compile_definitions(doctest_with_main INTERFACE DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)
  target_link_libraries(doctest_with_main INTERFACE doctest::doctest)
  message(STATUS "    Created   target: doctest_with_main")
endif ()
