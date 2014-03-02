TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH=/usr/local/include/SDL2

SOURCES += *.cpp \
    utils/utils.cpp \
    Time.cpp \
    utils/log.cpp \
    GameState.cpp \
    JewelSwap.cpp \
    JewelMove.cpp \
    model/BoardPos.cpp

OTHER_FILES += \
    Makefile \
    assets/SDL_test.xml \
    assets/map1.tmx \
    assets/board.tmx

HEADERS += \
    *.h \
    utils/utils.h \
    Time.h \
    utils/log.h \
    JewelSwap.h \
    JewelMove.h \
    model/BoardPos.h

