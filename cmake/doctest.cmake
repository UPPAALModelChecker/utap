find_package(doctest 2.4.8 QUIET)
if(doctest_FOUND)
  message(STATUS "Found doctest preinstalled.")
else(doctest_FOUND)
  message(STATUS "Failed to find doctest, going to make it from scratch.")
  include(FetchContent)
  set(DOCTEST_WITH_TESTS OFF CACHE BOOL "doctest tests")
  FetchContent_Declare(doctest
    GIT_REPOSITORY git@github.com:doctest/doctest.git
    GIT_TAG v2.4.9
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
