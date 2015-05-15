#-------------------------------------------------
#
# Project created by QtCreator 2015-05-05T01:16:44
#
#-------------------------------------------------

QT += core gui opengl

SOURCES += \
    main.cpp \
    maingame.cpp \
    projectile.cpp

HEADERS += \
    maingame.h \
    projectile.h

CONFIG += c++11

INCLUDEPATH += ../MyLE
LIBS += -L../../libs -lMyLE
PRE_TARGETDEPS += ../../libs/libMyLE.a

RESOURCES +=

DISTFILES += \
    .qmake.conf \
    resources/shaders/vertshader.vert \
    resources/shaders/vertshader.vert \
    resources/shaders/fragshader.frag

unix {
    copyfiles.commands += cp -r $$top_srcdir/resources $$top_builddir/
}

QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles
