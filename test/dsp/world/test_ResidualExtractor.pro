#-------------------------------------------------
#
# Project created by QtCreator 2013-05-14T23:30:15
#
#-------------------------------------------------

QT       += multimedia testlib

QT       -= gui

INCLUDEPATH += ../../../core/
DEPENDPATH += ../../../lib/

Release:LIBS += ../../../lib/stand.lib
Release:PRE_TARGETDEPS += ../../../lib/stand.lib
Debug:LIBS += ../../../lib/standd.lib
Debug:PRE_TARGETDEPS += ../../../lib/standd.lib

TARGET = test_ResidualExtractor
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += test_ResidualExtractor.cpp
