#-------------------------------------------------
#
# Project created by QtCreator 2016-11-02T16:06:03
#
#-------------------------------------------------

QT       += widgets dbus

TARGET = widgets
TEMPLATE = lib

DESTDIR = $(HOME)/.build/lib

include(../../platform/platform-lib.mk)

DEFINES += WIDGETS_LIBRARY

SOURCES += \
    indexdelegate.cpp \
    indexframe.cpp \
    indexmodel.cpp \
    indexview.cpp

HEADERS +=\
        widgets_global.h \
    indexdelegate.h \
    indexframe.h \
    indexmodel.h \
    indexview.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
