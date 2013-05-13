#-------------------------------------------------
#
# Project created by QtCreator 2013-05-11T01:51:30
#
#-------------------------------------------------

QT       += multimedia testlib

Release:LIBS += ../../../stand.lib
Release:PRE_TARGETDEPS = ../../../stand.lib
Debug:LIBS += ../../../standd.lib
Debug:PRE_TARGETDEPS = ../../../standd.lib
INCLUDEPATH += ../../../

TARGET = test_DioFfem
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += test_DioFfem.cpp
