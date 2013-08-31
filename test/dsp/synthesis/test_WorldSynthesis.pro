QT      += multimedia testlib
TEMPLATE = app
TARGET   = test_WorldSynthesis
CONFIG  += console
CONFIG  -= app_bundle

INCLUDEPATH += ../../../core/

SOURCES += \
    test_WorldSynthesis.cpp

include(../../StandTest.pri)
