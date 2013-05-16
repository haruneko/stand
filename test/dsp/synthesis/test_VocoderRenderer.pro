QT       += multimedia testlib

Release:LIBS += ../../../stand.lib
Release:PRE_TARGETDEPS = ../../../stand.lib
Debug:LIBS += ../../../standd.lib
Debug:PRE_TARGETDEPS = ../../../standd.lib
INCLUDEPATH += ../../../

TARGET = test_VocoderRenderer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \ 
    test_VocoderRenderer.cpp


