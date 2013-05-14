#-------------------------------------------------
#
# Project created by QtCreator 2013-05-14T20:58:03
#
#-------------------------------------------------

QT       += core multimedia

Release:LIBS += ../../stand.lib
Release:PRE_TARGETDEPS = ../../stand.lib
Debug:LIBS += ../../standd.lib
Debug:PRE_TARGETDEPS = ../../standd.lib
INCLUDEPATH += ../../

TARGET = WorldImageGenerator
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp
