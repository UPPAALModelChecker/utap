find_package(LibXml2 2.9.14 QUIET) # minimum version
#find_package(LibXml2 2.10.3 QUIET)

if(LibXml2_FOUND)
    message(STATUS "Found LibXml2 preinstalled: ${LIBXML2_INCLUDE_DIRS}")
else(LibXml2_FOUND)
    message(STATUS "Failed to find LibXml2, going to make it from scratch.")
    include(FetchContent)
    set(LIBXML2_SHARED_LIBS OFF CACHE BOOL "LibXml2 shared libraries")
    set(LIBXML2_WITH_FTP OFF CACHE BOOL "LibXml2 FTP support")
    set(LIBXML2_WITH_HTTP OFF CACHE BOOL "LibXml2 HTTP support")
    set(LIBXML2_WITH_ICONV OFF CACHE BOOL "LibXml2 ICONV")
    set(LIBXML2_WITH_LZMA OFF CACHE BOOL "LibXml2 LZMA")
    set(LIBXML2_WITH_PYTHON OFF CACHE BOOL "LibXml2 Python")
    set(LIBXML2_WITH_ZLIB OFF CACHE BOOL "LibXml2 libz")
    seT(LIBXML2_WITH_THREADS OFF CACHE BOOL "LibXml2 multithread support")
    set(LIBXML2_WITH_TESTS OFF CACHE BOOL "LibXml2 Tests")
    FetchContent_Declare(LibXml2
      URL https://download.gnome.org/sources/libxml2/2.11/libxml2-2.11.5.tar.xz
      URL_HASH SHA256=3727b078c360ec69fa869de14bd6f75d7ee8d36987b071e6928d4720a28df3a6
      #GIT_REPOSITORY https://gitlab.gnome.org/GNOME/libxml2 # often down
      #GIT_REPOSITORY https://github.com/GNOME/libxml2.git # mirror
      #GIT_TAG v2.11.5
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
