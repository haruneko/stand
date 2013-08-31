QT      += multimedia testlib
TEMPLATE = app
TARGET   = test_VocoderRenderer
CONFIG  += console
CONFIG  -= app_bundle

INCLUDEPATH += ../../../core/

SOURCES += \ 
    test_VocoderRenderer.cpp

include(../../StandTest.pri)
