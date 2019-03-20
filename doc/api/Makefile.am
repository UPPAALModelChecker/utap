EXTRA_DIST = @PACKAGE@.doxygen

CLEANFILES = *.html *.gif *.css *.png

noinst_DATA = index.html

VPATH=@srcdir@

index.html: @PACKAGE@.doxygen
	doxygen $<