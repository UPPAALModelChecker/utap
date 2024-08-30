find_package(doctest 2.4.8 QUIET)
if(doctest_FOUND)
  get_target_property(DOCTEST_INCLUDE_DIR doctest::doctest INTERFACE_INCLUDE_DIRECTORIES)
  message(STATUS "Found doctest preinstalled: ${DOCTEST_INCLUDE_DIR}")
else(doctest_FOUND)
  if (FIND_FATAL)
    message(FATAL_ERROR "Failed to find doctest")
  else (FIND_FATAL)
    message(STATUS "Failed to find doctest, going to make it from scratch.")
  endif (FIND_FATAL)
  include(FetchContent)
  set(DOCTEST_WITH_TESTS OFF CACHE BOOL "doctest tests")
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
