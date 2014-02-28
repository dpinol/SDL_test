TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH=/usr/local/include/SDL2

SOURCES += *.cpp \
    utils/utils.cpp

OTHER_FILES += \
    Makefile

HEADERS += \
    *.h \
    utils/utils.h

