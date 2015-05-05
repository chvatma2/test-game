#-------------------------------------------------
#
# Project created by QtCreator 2015-05-05T01:16:44
#
#-------------------------------------------------

QT += core gui opengl

SOURCES += \
    main.cpp \
    glwidget.cpp

HEADERS += \
    glwidget.h

INCLUDEPATH += ../MyLE
LIBS += -L../../libs -lMyLE
PRE_TARGETDEPS += ../../libs/libMyLE.a

RESOURCES +=

DISTFILES += \
    .qmake.conf

unix {
    copyfiles.commands += cp -r $$top_srcdir/resources $$top_builddir/resources
}

QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles
