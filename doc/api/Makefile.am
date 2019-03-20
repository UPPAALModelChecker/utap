EXTRA_DIST = @PACKAGE@.doxygen *.html *.png *.css

CLEANFILES = *.html *.gif *.css *.png

noinst_DATA = $(INDEX)

VPATH=@srcdir@

index.html: @PACKAGE@.doxygen
	doxygen $<

clean:
	rm -Rf *.html *.png *.css *.js *.map *.md5 search
