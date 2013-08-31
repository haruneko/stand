QT      += multimedia testlib
QT      -= gui
TEMPLATE = app
TARGET   = test_ResidualExtractor
CONFIG  += console
CONFIG  -= app_bundle

INCLUDEPATH += ../../../core/

SOURCES += test_ResidualExtractor.cpp

include(../../StandTest.pri)
