QT      += multimedia testlib
TARGET   = test_DioFfem
TEMPLATE = app
CONFIG  += console
CONFIG  -= app_bundle

INCLUDEPATH += ../../../core/

SOURCES += test_DioFfem.cpp

include(../../StandTest.pri)
