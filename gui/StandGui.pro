#-------------------------------------------------
#
# Project created by QtCreator 2013-03-20T01:23:00
#
#-------------------------------------------------

QT       += core gui multimedia

Release:TARGET = StandGui
Debug:TARGET = StandGuid

DESTDIR = ../lib/

TEMPLATE = lib
CONFIG += staticlib

HEADERS += \
    views/AbstractSequenceView.h \
    views/AbstractControlView.h \
    views/ControlCurveView.h \
    views/ControlGridView.h \
    views/AbstractGridView.h \
    utility/Utility.h \
    views/PianoPainter.h

SOURCES += \
    views/AbstractSequenceView.cpp \
    views/AbstractControlView.cpp \
    views/ControlCurveView.cpp \
    views/ControlGridView.cpp \
    views/AbstractGridView.cpp \
    utility/Utility.cpp \
    views/PianoPainter.cpp

