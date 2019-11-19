QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
TARGET = cardview

DEFINES += CARDVIEW_LIBRARY

DESTDIR = $$PWD/source/lib
DLLDESTDIR = $DESTDIR

INCLUDEPATH += source/

HEADERS += \
    source/include/cardview_common.h \
    source/include/cardview.h \
    source/include/cardviewwrappermodel.h \
    source/include/cardviewitemdelegate.h \
    source/include/cardviewsimpleitemdelegate.h \
    source/include/cardviewheaderitemdelegate.h

SOURCES += \
    source/cardview.cpp \
    source/cardviewwrappermodel.cpp \
    source/cardviewitemdelegate.cpp \
    source/cardviewsimpleitemdelegate.cpp \
    source/cardviewheaderitemdelegate.cpp
