QT      += multimedia testlib
TEMPLATE = app
TARGET   = test_PlatinumSeem
CONFIG  += console
CONFIG  -= app_bundle

INCLUDEPATH += ../../../core/

SOURCES += test_PlatinumSeem.cpp

include(../../StandTest.pri)
