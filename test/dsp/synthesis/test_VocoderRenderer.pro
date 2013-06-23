QT       += multimedia testlib

INCLUDEPATH += ../../../core/
DEPENDPATH += ../../../lib/

Release:LIBS += ../../../lib/stand.lib
Release:PRE_TARGETDEPS += ../../../lib/stand.lib
Debug:LIBS += ../../../lib/standd.lib
Debug:PRE_TARGETDEPS += ../../../lib/standd.lib

TARGET = test_VocoderRenderer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \ 
    test_VocoderRenderer.cpp


