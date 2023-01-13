find_package(doctest 2.4.8 QUIET)
if(doctest_FOUND)
  message(STATUS "Found doctest preinstalled.")
else(doctest_FOUND)
  message(STATUS "Failed to find doctest, going to make it from scratch.")
  include(FetchContent)
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
    CMAKE_ARGS -DDOCTEST_WITH_TESTS=OFF
    FIND_PACKAGE_ARGS NAMES doctest
  )
  FetchContent_MakeAvailable(doctest)
endif(doctest_FOUND)
