find_package(doctest 2.4.8 QUIET)
if(doctest_FOUND)
  get_target_property(DOCTEST_INCLUDE_DIR doctest::doctest INTERFACE_INCLUDE_DIRECTORIES)
  message(STATUS "Found doctest preinstalled: ${DOCTEST_INCLUDE_DIR}")
else(doctest_FOUND)
  if (FIND_FATAL)
    message(FATAL_ERROR "Could not find doctest in ${CMAKE_PREFIX_PATH}")
  endif (FIND_FATAL)
  message(STATUS "Failed to find doctest, going to make it from scratch.")
  include(FetchContent)
  set(DOCTEST_WITH_TESTS OFF CACHE BOOL "doctest tests")
  set(DOCTEST_WITH_MAIN_IN_STATIC_LIB ON CACHE BOOL "static lib (cmake target) with a default main entry point")
  set(DOCTEST_NO_INSTALL ON CACHE BOOL "Skip the installation process")
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
  FetchContent_MakeAvailable(doctest)
  message(STATUS "Got doctest.")
endif(doctest_FOUND)
