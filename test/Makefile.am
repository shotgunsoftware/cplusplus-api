
check_PROGRAMS = simpletest \
                 listProjects 


AM_CPPFLAGS = -I$(top_srcdir)/lib @XMLRPC_CFLAGS@

simpletest_SOURCES = simpletest.cpp
simpletest_LDADD = -L$(top_builddir)/lib/Shotgun -lShotgun @XMLRPC_LDADD@
simpletest_LDFLAGS = @XMLRPC_LDFLAGS@

listProjects_SOURCES = listProjects.cpp
listProjects_LDADD = -L$(top_builddir)/lib/Shotgun -lShotgun @XMLRPC_LDADD@
listProjects_LDFLAGS = @XMLRPC_LDFLAGS@


TESTS = simpletest \
        listProjects 
