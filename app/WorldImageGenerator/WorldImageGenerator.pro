TEMPLATE = app
QT       += core multimedia

INCLUDEPATH += ../../core/

TARGET = WorldImageGenerator
CONFIG   += console
CONFIG   -= app_bundle

SOURCES += main.cpp

include(../StandApps.pri)
