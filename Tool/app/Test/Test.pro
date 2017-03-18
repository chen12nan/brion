TEMPLATE = app
TARGET = Test

QT += core gui widgets sql network webkitwidgets

include(../../platform/platform-app.mk)

SOURCES += \
    main.cpp \
    DisplayTableForm.cpp

HEADERS += \
    DisplayTableForm.h

FORMS += \
    DisplayTableForm.ui

CITIES_PATH=$$PWD/data/timezone.db

DEFINES += CITIES_DATABASE_PATH=\\\"$$CITIES_PATH\\\"

message(DATAPATH)
