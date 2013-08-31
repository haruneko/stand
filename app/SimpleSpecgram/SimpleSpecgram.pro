QT      += core multimedia
TEMPLATE = app
TARGET   = SimpleSpecgram
CONFIG  += console
CONFIG  -= app_bundle

INCLUDEPATH += ../../core/

SOURCES += main.cpp

include(../StandApps.pri)
