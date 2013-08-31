QT      += multimedia testlib
TEMPLATE = app
TARGET   = test_StarSeem
CONFIG  += console
CONFIG  -= app_bundle

INCLUDEPATH += ../../../core/

SOURCES += test_StarSeem.cpp

include(../../StandTest.pri)
