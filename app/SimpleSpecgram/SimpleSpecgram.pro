QT       += core multimedia

Release:LIBS += ../../stand.lib
Release:PRE_TARGETDEPS = ../../stand.lib
Debug:LIBS += ../../standd.lib
Debug:PRE_TARGETDEPS = ../../standd.lib
INCLUDEPATH += ../../

TARGET = SimpleSpecgram
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp
