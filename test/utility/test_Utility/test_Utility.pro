QT      += testlib widgets
TEMPLATE = app
TARGET   = test_Utility
CONFIG  += console
CONFIG  -= app_bundle

INCLUDEPATH += ../../../gui/

SOURCES += test_Utility.cpp

include(../../StandTest.pri)
