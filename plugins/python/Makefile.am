
SUBDIRS = test

SIP_SOURCE = sip/_shotgun.sip           \
             sip/exceptions.sip         \
             sip/mappedTypes.sip        \
             sip/List.sip               \
             sip/Dict.sip               \
             sip/FilterBy.sip           \
             sip/SortBy.sip             \
             sip/Fields.sip             \
             sip/Asset.sip              \
             sip/Delivery.sip           \
             sip/Element.sip            \
             sip/Entity.sip             \
             sip/Group.sip              \
             sip/HumanUser.sip          \
             sip/Method.sip             \
             sip/NoteMixin.sip          \
             sip/Note.sip               \
             sip/Playlist.sip           \
             sip/Project.sip            \
             sip/PublishEvent.sip       \
             sip/ReviewItem.sip         \
             sip/Review.sip             \
             sip/Sequence.sip           \
             sip/Shotgun.sip            \
             sip/Shot.sip               \
             sip/TaskMixin.sip          \
             sip/Task.sip               \
             sip/Version.sip            \
             sip/CustomEntity.sip

EXTRA_DIST = configure.py $(SIP_SOURCE) shotgun.py

BUILT_SOURCES = _shotgun.so

# Export these so they can be picked up by ./configure.py
export XMLRPC_CFLAGS
export XMLRPC_LDFLAGS
export XMLRPC_LDADD
export DEFS

_shotgun.so: configure.py $(SIP_SOURCE)
	mkdir -p src
	./configure.py
	make -C src
	mv src/_shotgun.so .

CLEANFILES = _shotgun.so src/*.o

maintainer-clean:
	rm -rf src _shotgun.so Makefile
