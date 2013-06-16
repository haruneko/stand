#-------------------------------------------------
#
# Project created by QtCreator 2013-05-14T20:58:03
#
#-------------------------------------------------

QT       += core multimedia

INCLUDEPATH += ../../core/
DEPENDPATH += ../../lib/

Release:LIBS += ../../lib/stand.lib
Release:PRE_TARGETDEPS = ../../lib/stand.lib
Debug:LIBS += ../../lib/standd.lib
Debug:PRE_TARGETDEPS = ../../lib/standd.lib

TARGET = WorldImageGenerator
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp
