
check_PROGRAMS = simpletest

simpletest_SOURCES = simpletest.cpp

AM_CPPFLAGS = -I$(top_srcdir)/lib @XMLRPC_CFLAGS@

simpletest_LDADD = -L$(top_builddir)/lib/Shotgun -lShotgun @XMLRPC_LDADD@
simpletest_LDFLAGS = @XMLRPC_LDFLAGS@

TESTS = simpletest
