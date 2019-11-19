QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += source/

HEADERS = \
    source/simplecardentitymodel.h

SOURCES = \
    source/simplecardentitymodel.cpp \
    source/main.cpp


unix|win32: LIBS += -L$$PWD/../cardview_library/source/lib/ -lcardview

INCLUDEPATH += $$PWD/../cardview_library/source/include
DEPENDPATH += $$PWD/../cardview_library/source/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../cardview_library/source/lib/cardview.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../cardview_library/source/lib/libcardview.a

RESOURCES += \
    resources.qrc
