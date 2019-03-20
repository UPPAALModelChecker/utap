## Process this file with automake to produce Makefile.in

# libutap - Uppaal Timed Automata Parser.
# Copyright (C) 2002-2015 Uppsala University and Aalborg University.
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

bin_PROGRAMS = pretty syntaxcheck taflow tracer
lib_LIBRARIES = libutap.a
includedir = ${prefix}/include/utap
include_HEADERS = utap/abstractbuilder.h utap/builder.h utap/common.h utap/expression.h utap/expressionbuilder.h utap/position.h utap/prettyprinter.h utap/signalflow.h utap/statement.h utap/statementbuilder.h utap/symbols.h utap/system.h utap/systembuilder.h utap/type.h utap/typechecker.h utap/utap.h utap/xmlwriter.h

pretty_SOURCES = pretty.cpp

syntaxcheck_SOURCES = syntaxcheck.cpp

taflow_SOURCES = taflow.cpp

tracer_SOURCES = tracer.cpp

libutap_a_SOURCES = abstractbuilder.cpp expression.cpp expressionbuilder.cpp position.cpp prettyprinter.cpp signalflow.cpp statement.cpp statementbuilder.cpp symbols.cpp system.cpp systembuilder.cpp type.cpp typechecker.cpp typeexception.cpp xmlreader.cpp xmlwriter.cpp tags.gperf parser.yy libparser.h
EXTRA_libutap_a_SOURCES = lexer.ll lexer.cc tags.gperf tags.cc keywords.gperf keywords.cc

pretty_LDADD = libutap.a $(XML_LIBS)
syntaxcheck_LDADD = libutap.a $(XML_LIBS)
taflow_LDADD = libutap.a $(XML_LIBS)
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
	if [ -f parser.tab.cc ]; then\
		mv parser.tab.cc parser.cc ;\
	else\
		mv -f parser.tab.c parser.cc;\
	fi

lexer.cc: lexer.ll
	$(LEX) -Putap_ -o$@ $< 
