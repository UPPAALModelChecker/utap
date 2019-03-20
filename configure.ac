# libutap - Uppaal Timed Automata Parser.
# Copyright (C) 2002 Uppsala University and Aalborg University.
# 
# This library is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as
# published by the Free Software Foundation; either version 2.1 of the
# License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
# USA

AC_INIT(UPPAAL TA Parser Library, 0.60, behrmann@cs.auc.dk, libutap)

AC_PREREQ(2.50)

AM_INIT_AUTOMAKE(libutap, 0.60)
AM_CONFIG_HEADER(config.h)
AC_CONFIG_SRCDIR(src/pretty.cpp)
AC_CONFIG_AUX_DIR(.)
     
dnl Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_YACC
AC_PROG_RANLIB
AM_PROG_LEX
AC_ISC_POSIX

AM_MISSING_PROG([GPERF], [gperf])

dnl Check if documentation should be built

AC_SUBST(INDEX)

enableval=no
AC_MSG_CHECKING([if documentation should be generated])
AC_ARG_ENABLE(documentation,
[  --enable-documentation   generate documentation from source])
case "${enableval}" in
yes)
  AC_MSG_RESULT(yes)
  AM_MISSING_PROG([DOXYGEN], [doxygen])
  INDEX="index.html"
  ;;

no)
  AC_MSG_RESULT(no)
  INDEX=""
  ;;

*)
  AC_MSG_ERROR([bad value ${enableval} --enable-documentation, needs yes or no])
  ;;
esac
 
dnl Checks for libraries.
     
dnl Checks for header files.
AC_STDC_HEADERS
AC_HAVE_HEADERS(string.h fcntl.h sys/file.h sys/param.h)
     
dnl Checks for library functions.
AC_FUNC_ALLOCA
     
dnl Check for st_blksize in struct stat
AC_ST_BLKSIZE
     
dnl Check for libxml2
AC_ARG_WITH(libxml2-prefix, 
[  --with-libxml2-prefix=[=DIR] set prefix for libxml2 installation],
[
  AC_PATH_PROG(XML_CONFIG, xml2-config, , $withval/bin)
], [
  AC_PATH_PROG(XML_CONFIG, xml2-config)
])

if test -z "$XML_CONFIG"; then
  AC_MSG_ERROR("xml2-config was not found");
fi

XML_CFLAGS=`$XML_CONFIG --cflags 2>/dev/null`
XML_LIBS=`$XML_CONFIG --libs 2>/dev/null`

AC_SUBST(XML_CONFIG)
AC_SUBST(XML_CFLAGS)
AC_SUBST(XML_LIBS)

dnl Check for debug flags
OPT_FLAGS=""
enableval=no
AC_MSG_CHECKING([whether to compile with debug info])
AC_ARG_ENABLE(debugging,
[  --enable-debugging      compile with debugging information])
case "${enableval}" in
yes)
  AC_MSG_RESULT(yes)
  OPT_FLAGS="$OPT_FLAGS -g"
  ;;
no)
  AC_MSG_RESULT(no)
  OPT_FLAGS="$OPT_FLAGS -O2"
  ;;
*)
  AC_MSG_ERROR([bad value ${enableval} for --enable-debugging, needs yes or no])
  ;;
esac

enableval=no
AC_MSG_CHECKING([whether to enable checking of run-time assertions])
AC_ARG_ENABLE(assertions,
[  --enable-assertions     check run-time assertions])
case "${enableval}" in
yes)
  AC_MSG_RESULT(yes)
  ;;
no)
  AC_MSG_RESULT(no)
  AC_DEFINE(NDEBUG, 1, [Assertions are disabled when this is defined])
  OPT_FLAGS="$OPT_FLAGS -DNDEBUG"
  ;;
*)
  AC_MSG_ERROR([bad value ${enableval} --enable-assertions, needs yes or no])
  ;;
esac

dnl Check target os
case "$target_alias" in
  *mingw32)
     LIBS="-liberty $LIBS"
     AC_MSG_RESULT([using liberty library for mingw32 target])
     ;;
esac

CFLAGS="$OPT_FLAGS"
CPPFLAGS="$OPT_FLAGS"

AC_CONFIG_FILES([Makefile src/Makefile doc/Makefile doc/api/Makefile])
AC_OUTPUT
