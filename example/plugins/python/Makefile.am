
SUBDIRS = test

SIP_SOURCE = sip/_siteshotgun.sip       \
             sip/SiteProject.sip        \
             sip/SiteShotgun.sip 

EXTRA_DIST = siteconfigure.py $(SIP_SOURCE) siteshotgun.py

BUILT_SOURCES = _siteshotgun.so

# Export these so they can be picked up by ./siteconfigure.py
export XMLRPC_CFLAGS
export XMLRPC_LDFLAGS
export XMLRPC_LDADD
export DEFS

_siteshotgun.so: siteconfigure.py $(SIP_SOURCE)
	mkdir -p src
	./siteconfigure.py
	make -C src
	mv src/_siteshotgun.so .

CLEANFILES = _siteshotgun.so src/*.o

maintainer-clean:
	rm -rf src _siteshotgun.so Makefile



