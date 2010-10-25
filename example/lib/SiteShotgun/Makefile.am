
lib_LTLIBRARIES = libSiteShotgun.la

INCLUDES = -I$(top_srcdir)/lib -I$(top_srcdir)/example/lib

libSiteShotgun_la_LIBADD = @XMLRPC_LDADD@ @XMLRPC_LDFLAGS@
libSiteShotgun_la_CPPFLAGS = @XMLRPC_CFLAGS@

libSiteShotgun_la_SOURCES = SiteProject.cpp               \
                            SiteShotgun.cpp            

include_HEADERS = SiteProject.h             \
                  SiteShotgun.h
