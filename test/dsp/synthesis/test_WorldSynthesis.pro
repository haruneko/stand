#-------------------------------------------------
#
# Project created by QtCreator 2013-05-11T01:51:30
#
#-------------------------------------------------

QT       += multimedia testlib

INCLUDEPATH += ../../../core/
DEPENDPATH += ../../../lib/

Release:LIBS += ../../../lib/stand.lib
Release:PRE_TARGETDEPS += ../../../lib/stand.lib
Debug:LIBS += ../../../lib/standd.lib
Debug:PRE_TARGETDEPS += ../../../lib/standd.lib

TARGET = test_WorldSynthesis
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    test_WorldSynthesis.cpp


