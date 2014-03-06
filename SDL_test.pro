TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH=/usr/local/include/SDL2

SOURCES += *.cpp \
    utils/*.cpp \
    model/*.cpp \
    JewelDrag.cpp \
    model/test/*.cpp \
    utils/init.cpp \
    MovingObject.cpp


OTHER_FILES += \
    Makefile \
    assets/*.xml \
    assets/*.tmx \
    assets/*.png

HEADERS += \
    *.h \
    utils/*.h \
    model/*.h \
    model/test/*.h \
    JewelDrag.h \
    utils/init.h \
    MovingObject.h

