
check_PROGRAMS = testSiteProject testSiteReference


AM_CPPFLAGS = -I$(top_srcdir)/example/lib -I$(top_srcdir)/lib @XMLRPC_CFLAGS@

testSiteProject_SOURCES = testSiteProject.cpp
testSiteProject_LDADD = -L$(top_builddir)/example/lib/SiteShotgun -L$(top_builddir)/lib/Shotgun -lSiteShotgun -lShotgun @XMLRPC_LDADD@
testSiteProject_LDFLAGS = @XMLRPC_LDFLAGS@

testSiteReference_SOURCES = testSiteReference.cpp
testSiteReference_LDADD = -L$(top_builddir)/example/lib/SiteShotgun -L$(top_builddir)/lib/Shotgun -lSiteShotgun -lShotgun @XMLRPC_LDADD@
testSiteReference_LDFLAGS = @XMLRPC_LDFLAGS@


TESTS = testSiteProject testSiteReference

