TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH=/usr/local/include/SDL2

SOURCES += *.cpp \
    utils/utils.cpp \
    Time.cpp \
    utils/log.cpp \
    GameState.cpp

OTHER_FILES += \
    Makefile

HEADERS += \
    *.h \
    utils/utils.h \
    Time.h \
    utils/log.h

