#-------------------------------------------------
#
# Project created by QtCreator 2013-03-20T01:23:00
#
#-------------------------------------------------

QT       += core gui multimedia

Release:TARGET = StandGui
Debug:TARGET = StandGuid

DESTDIR = ../lib/
INCLUDEPATH += ../libvsq/

TEMPLATE = lib
CONFIG += staticlib

HEADERS += \
    views/AbstractSequenceView.h \
    views/ControlCurveView.h \
    views/AbstractGridView.h \
    utility/Utility.h \
    views/PianoPainter.h \
    views/NoteView.h \
    models/Selection.h \
    views/BeatView.h \
    views/TempoView.h \
    views/AbstractLabelView.h \
    views/SingerView.h \
    views/TrackSelectionView.h \
    views/PianoView.h \
    models/ControlCurveSelection.h \
    views/ControlCurvePainter.h \
    views/AbstractControlPainter.h \
    controllers/ControlCurveSelector.h \
    views/ControlCurveNameView.h \
    models/SequenceModel.h \
    models/EventSelection.h \
    models/actions/NoteChangeAction.h \
    controllers/NoteSelector.h \
    controllers/NoteCreator.h \
    controllers/NoteModifier.h

SOURCES += \
    views/AbstractSequenceView.cpp \
    views/ControlCurveView.cpp \
    views/AbstractGridView.cpp \
    utility/Utility.cpp \
    views/PianoPainter.cpp \
    views/NoteView.cpp \
    models/Selection.cpp \
    views/BeatView.cpp \
    views/TempoView.cpp \
    views/AbstractLabelView.cpp \
    views/SingerView.cpp \
    views/TrackSelectionView.cpp \
    views/PianoView.cpp \
    models/ControlCurveSelection.cpp \
    views/ControlCurvePainter.cpp \
    views/AbstractControlPainter.cpp \
    controllers/ControlCurveSelector.cpp \
    views/ControlCurveNameView.cpp \
    models/SequenceModel.cpp \
    models/EventSelection.cpp \
    models/actions/NoteChangeAction.cpp \
    controllers/NoteSelector.cpp \
    controllers/NoteCreator.cpp \
    controllers/NoteModifier.cpp

