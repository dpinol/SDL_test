TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH=/usr/local/include/SDL2

SOURCES += *.cpp \
    Game.cpp

OTHER_FILES += \
    Makefile

HEADERS += \
    Game.h

