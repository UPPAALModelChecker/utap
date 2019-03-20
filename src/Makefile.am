## Process this file with automake to produce Makefile.in

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

VPATH = @srcdir@

bin_PROGRAMS = pretty
lib_LIBRARIES = libutap.a
EXTRA_PROGRAMS = decl_check
includedir = ${prefix}/include/utap
include_HEADERS = utap/builder.hh utap/common.hh utap/expression.hh utap/statement.hh utap/symbols.hh utap/system.hh utap/typechecker.hh utap/utap.hh utap/systembuilder.hh utap/rangechecker.hh

pretty_SOURCES = pretty.cc 
decl_check_SOURCES = decl_check.cc

libutap_a_SOURCES = expression.cc system.cc typechecker.cc typeexception.cc symbols.cc xmlreader.cc tags.gperf statement.cc error.cc parser.yy libparser.hh systembuilder.cc rangechecker.cc
EXTRA_libutap_a_SOURCES = lexer.ll lexer.cc tags.gperf tags.cc keywords.gperf keywords.cc

LDADD = libutap.a $(XML_LIBS)
AM_CFLAGS = @CFLAGS@ $(XML_CFLAGS) -Wall
AM_CPPFLAGS = @CPPFLAGS@ $(XML_CFLAGS) -Wall

BUILT_SOURCES = tags.cc keywords.cc lexer.cc

# Handling the Gperf code
GPERFFLAGS = -C -E -t -L C++ -c 

tags.cc: tags.gperf
	if $(GPERF) $(GPERFFLAGS) -K str -Z Tags \
		$< >$@t; then \
	mv $@t $@; \
	elif $(GPERF) --version >/dev/null 2>&1; then \
		rm $@t; \
		exit 1; \
	else \
		rm $@t; \
		touch $@; \
	fi

keywords.cc: keywords.gperf
	if $(GPERF) $(GPERFFLAGS) -Z Keywords \
		$< >$@t; then \
	mv $@t $@; \
	elif $(GPERF) --version >/dev/null 2>&1; then \
		rm $@t; \
		exit 1; \
	else \
		rm $@t; \
		touch $@; \
	fi

# Handling the parser and the lexer
parser.cc parser.h: parser.yy lexer.cc
	$(YACC) -p utap_ -b parser $<
	$(RM) parser.cc
	mv parser.tab.c parser.cc

lexer.cc: lexer.ll
	$(LEX) -Putap_ -o$@ $< 
