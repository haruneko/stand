#-------------------------------------------------
#
# Project created by QtCreator 2013-06-18T01:15:33
#
#-------------------------------------------------

QT       += core gui

TARGET = SimpleSequenceView
TEMPLATE = app

INCLUDEPATH += ../../gui/
DEPENDPATH += ../../lib/

Release:LIBS += ../../lib/StandGui.lib
Release:PRE_TARGETDEPS += ../../lib/StandGui.lib
Debug:LIBS += ../../lib/StandGuid.lib
Debug:PRE_TARGETDEPS += ../../lib/StandGuid.lib

SOURCES += main.cpp\
        SequenceWindow.cpp

HEADERS  += SequenceWindow.h

FORMS    += SequenceWindow.ui
