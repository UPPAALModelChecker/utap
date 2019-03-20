EXTRA_DIST = @PACKAGE@.doxygen *.html *.png *.css

CLEANFILES = *.html *.gif *.css *.png

noinst_DATA = index.html

VPATH=@srcdir@

index.html: @PACKAGE@.doxygen
	doxygen $<