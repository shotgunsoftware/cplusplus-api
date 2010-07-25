
AM_CPPFLAGS = -I$(top_srcdir)/lib

lib_LTLIBRARIES = libShotgun.la

libShotgun_la_SOURCES = Asset.cpp               \
                        Delivery.cpp            \
                        Element.cpp             \
                        Entity.cpp              \
                        Group.cpp               \
                        Method.cpp              \
                        Note.cpp                \
                        NoteMixin.cpp           \
                        Playlist.cpp            \
                        PublishEvent.cpp        \
                        Review.cpp              \
                        ReviewItem.cpp          \
                        Sequence.cpp            \
                        Shot.cpp                \
                        Shotgun.cpp             \
                        Project.cpp             \
                        Task.cpp                \
                        TaskMixin.cpp           \
                        Type.cpp                \
                        HumanUser.cpp           \
                        Version.cpp             \
                        utils.cpp

include_HEADERS = Asset.h                       \
                  Delivery.h                    \
                  Element.h                     \
                  Entity.h                      \
                  Group.h                       \
                  Method.h                      \
                  Note.h                        \
                  NoteMixin.h                   \
                  Playlist.h                    \
                  PublishEvent.h                \
                  Review.h                      \
                  ReviewItem.h                  \
                  Sequence.h                    \
                  Shotgun.h                     \
                  Shot.h                        \
                  Project.h                     \
                  Task.h                        \
                  TaskMixin.h                   \
                  Type.h                        \
                  HumanUser.h                   \
                  Version.h                     \
                  utils.h


libShotgun_la_LIBADD = @XMLRPC_LDADD@ @XMLRPC_LDFLAGS@

