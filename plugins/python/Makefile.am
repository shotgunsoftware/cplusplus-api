
EXTRA_DIST = configure.py               \
             sip/Asset.sip              \
             sip/Daily.sip              \
             sip/DeliveryItem.sip       \
             sip/Delivery.sip           \
             sip/Element.sip            \
             sip/Entity.sip             \
             sip/exceptions.sip         \
             sip/Group.sip              \
             sip/mappedTypes.sip        \
             sip/Method.sip             \
             sip/NoteMixin.sip          \
             sip/Note.sip               \
             sip/Playlist.sip           \
             sip/PublishEvent.sip       \
             sip/Reference.sip          \
             sip/ReviewItem.sip         \
             sip/Review.sip             \
             sip/Sequence.sip           \
             sip/_shotgun.sip           \
             sip/Shotgun.sip            \
             sip/Shot.sip               \
             sip/Show.sip               \
             sip/TaskMixin.sip          \
             sip/Task.sip               \
             sip/User.sip

BUILT_SOURCES = _shotgun.so

_shotgun.so: 
	mkdir -p src
	./configure.py
	make -C src
	mv src/_shotgun.so .

CLEANFILES = _shotgun.so src/*.o

maintainer-clean:
	rm -rf src _shotgun.so Makefile


