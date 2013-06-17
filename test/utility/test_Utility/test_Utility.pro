#-------------------------------------------------
#
# Project created by QtCreator 2013-06-17T22:11:03
#
#-------------------------------------------------

QT       += testlib

TARGET = test_Utility
CONFIG   += console
CONFIG   -= app_bundle

INCLUDEPATH += ../../../gui/
DEPENDPATH += ../../../lib/

Release:LIBS += ../../../lib/StandGui.lib
Release:PRE_TARGETDEPS = ../../../lib/StandGui.lib
Debug:LIBS += ../../../lib/StandGuid.lib
Debug:PRE_TARGETDEPS = ../../../lib/StandGuid.lib

TEMPLATE = app


SOURCES += test_Utility.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
