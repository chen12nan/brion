
TARGET = epweather
TEMPLATE = lib
DESTDIR = $(HOME)/.build/lib

QT += sql core-private network widgets

include(../../platform/platform-lib.mk)

DEFINES += WEATHER_LIBRARY


unix {
    target.path = /usr/lib
    INSTALLS += target
}

HEADERS += \
    epweather_global.h \
    weatheritem.h \
    weatherinterface.h \
    weatherrequest.h \
    weatherwidget.h

SOURCES += \
    weatheritem.cpp \
    weatherinterface.cpp \
    weatherrequest.cpp \
    weatherwidget.cpp

RESOURCES += \
    weather.qrc
