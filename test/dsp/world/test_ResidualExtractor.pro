#-------------------------------------------------
#
# Project created by QtCreator 2013-05-14T23:30:15
#
#-------------------------------------------------

QT       += multimedia testlib

QT       -= gui

Release:LIBS += ../../../stand.lib
Release:PRE_TARGETDEPS = ../../../stand.lib
Debug:LIBS += ../../../standd.lib
Debug:PRE_TARGETDEPS = ../../../standd.lib
INCLUDEPATH += ../../../

TARGET = test_ResidualExtractor
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += test_ResidualExtractor.cpp
