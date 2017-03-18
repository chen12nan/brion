#-------------------------------------------------
#
# Project created by QtCreator 2016-09-30T14:10:15
#
#-------------------------------------------------

QT       += widgets sql

CONFIG += c++11

TARGET = datetime
TEMPLATE = lib

CITIES_PATH=$$PWD/../../data
DEFINES += CITIES_DATABASE_PATH=\\\"$$CITIES_PATH\\\"

DEFINES += DATETIME_LIBRARY

include(../../platform/platform-lib.mk)

SOURCES += datetime.cpp \
    clock.cpp \
    datetimeutil.cpp \
    editdatewidget.cpp \
    chosedialog.cpp

HEADERS += datetime.h\
        datetime_global.h \
    clock.h \
    datetimeutil.h \
    editdatewidget.h \
    chosedialog.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    resource.qrc
