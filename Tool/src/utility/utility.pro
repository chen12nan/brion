#-------------------------------------------------
#
# Project created by QtCreator 2015-12-29T16:41:37
#
#-------------------------------------------------

include(../../platform/platform-lib.mk)

TARGET = eputility
TEMPLATE = lib

QT += sql network

DEFINES += UTILITY_LIBRARY

CONFIG += link_pkgconfig

PKGCONFIG += geoip

SOURCES += utility.cpp \
    vcardparser.cpp \
    networkutil.cpp \
    stringutil.cpp

HEADERS += utility.h\
        utility_global.h \
    vcardparser.h \
    networkutil.h \
    stringutil.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
