find_package(doctest 2.4.11 QUIET)
if(doctest_FOUND)
  if (TARGET doctest::doctest_with_main)
    message(STATUS "Found doctest::doctest_with_main")
    add_library(doctest_main INTERFACE)
    target_link_libraries(doctest_main INTERFACE doctest::doctest_with_main)
  else(TARGET doctest::doctest_with_main) # workaround for old doctest
    message(STATUS "Workaround for doctest::doctest_with_main")
    add_library(doctest_main INTERFACE)
    target_compile_definitions(doctest_main INTERFACE DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)
    target_link_libraries(doctest_main INTERFACE doctest::doctest)
  endif(TARGET doctest::doctest_with_main)
  message(STATUS "Found doctest preinstalled: ${doctest_DIR}")
else(doctest_FOUND)
  if (FIND_FATAL)
    message(FATAL_ERROR "Failed to find doctest")
  else (FIND_FATAL)
    message(STATUS "Failed to find doctest, going to make it from scratch.")
  endif (FIND_FATAL)
  include(FetchContent)
  set(DOCTEST_WITH_TESTS OFF CACHE BOOL "doctest tests and examples")
  set(DOCTEST_WITH_MAIN_IN_STATIC_LIB ON CACHE BOOL "Build static lib for doctest::doctest_with_main")
  set(DOCTEST_NO_INSTALL OFF CACHE BOOL "Skip the installation process")
  set(DOCTEST_USE_STD_HEADERS OFF CACHE BOOL "Use std headers")
  FetchContent_Declare(doctest
    GIT_REPOSITORY git@github.com:doctest/doctest.git
    GIT_TAG v2.4.11
    GIT_SHALLOW ON
    GIT_PROGRESS ON
    UPDATE_DISCONNECTED ON
    USES_TERMINAL_DOWNLOAD ON
    USES_TERMINAL_CONFIGURE ON
    USES_TERMINAL_BUILD ON
    USES_TERMINAL_INSTALL ON
    FIND_PACKAGE_ARGS NAMES doctest
  )
  FetchContent_GetProperties(doctest)
  if (doctest_POPULATED)
    message(STATUS "Found populated doctest: ${doctest_SOURCE_DIR}")
  else (doctest_POPULATED)
    FetchContent_Populate(doctest)
    add_subdirectory(${doctest_SOURCE_DIR} ${doctest_BINARY_DIR} EXCLUDE_FROM_ALL)
    if (TARGET doctest::doctest_with_main)
      message(STATUS "Found doctest::doctest_with_main")
      add_library(doctest_main INTERFACE)
      target_link_libraries(doctest_main INTERFACE doctest::doctest_with_main)
    else(TARGET doctest::doctest_with_main) # workaround for old doctest
      message(STATUS "Workaround for doctest::doctest_with_main")
      add_library(doctest_main INTERFACE)
      target_compile_definitions(doctest_main INTERFACE DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)
      target_link_libraries(doctest_main INTERFACE doctest::doctest)
    endif(TARGET doctest::doctest_with_main)
    message(STATUS "Got doctest: ${doctest_SOURCE_DIR}")
  endif (doctest_POPULATED)
endif(doctest_FOUND)
