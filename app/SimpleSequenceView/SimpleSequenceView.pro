QT      += core widgets
TARGET   = SimpleSequenceView
TEMPLATE = app

INCLUDEPATH += ../../gui/ ../../libvsq/

SOURCES += main.cpp \
        SequenceWindow.cpp

HEADERS  += SequenceWindow.h

FORMS    += SequenceWindow.ui

include(../StandApps.pri)
