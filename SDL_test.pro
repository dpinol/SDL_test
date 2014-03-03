TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH=/usr/local/include/SDL2

SOURCES += *.cpp \
    utils/*.cpp \
    model/*.cpp \
    model/JewelStrike.cpp \
    model/Jewel.cpp \
    model/Board.cpp \
    model/test/JewelStrikeTest.cpp \
    model/test/main.cpp


OTHER_FILES += \
    Makefile \
    assets/*.xml \
    assets/*.tmx \
    assets/*.png

HEADERS += \
    *.h \
    utils/*.h \
    model/*.h \
    model/BoardPos.h \
    model/JewelStrike.h \
    model/Jewel.h \
    model/Board.h \
    model/test/JewelStrikeTest.h

