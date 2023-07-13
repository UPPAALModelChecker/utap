find_package(LibXml2 2.9.14 QUIET) # minimum version
#find_package(LibXml2 2.10.3 QUIET)

if(LibXml2_FOUND)
    message(STATUS "Found LibXml2 preinstalled: ${LIBXML2_INCLUDE_DIRS}")
else(LibXml2_FOUND)
    message(STATUS "Failed to find LibXml2, going to make it from scratch.")
    include(FetchContent)
    set(LIBXML2_WITH_FTP OFF CACHE BOOL "LibXml2 FTP support")
    set(LIBXML2_WITH_HTTP OFF CACHE BOOL "LibXml2 HTTP support")
    set(LIBXML2_WITH_ICONV OFF CACHE BOOL "LibXml2 ICONV")
    set(LIBXML2_WITH_LZMA OFF CACHE BOOL "LibXml2 LZMA")
    set(LIBXML2_WITH_PYTHON OFF CACHE BOOL "LibXml2 Python")
    set(LIBXML2_WITH_ZLIB OFF CACHE BOOL "LibXml2 libz")
    seT(LIBXML2_WITH_THREADS OFF CACHE BOOL "LibXml2 multithread support")
    set(LIBXML2_WITH_TESTS OFF CACHE BOOL "LibXml2 Tests")
    FetchContent_Declare(LibXml2
            GIT_REPOSITORY https://gitlab.gnome.org/GNOME/libxml2
            GIT_TAG v2.10.3
            GIT_SHALLOW ON
            GIT_PROGRESS ON
            UPDATE_DISCONNECTED ON
            USES_TERMINAL_DOWNLOAD ON
            USES_TERMINAL_CONFIGURE ON
            USES_TERMINAL_BUILD ON
            USES_TERMINAL_INSTALL ON
            FIND_PACKAGE_ARGS NAMES LibXml2
            )
    FetchContent_MakeAvailable(LibXml2)
    message(STATUS "Got LibXml2.")
endif(LibXml2_FOUND)
