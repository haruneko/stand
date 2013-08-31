QT      += core widgets multimedia
TEMPLATE = app
TARGET   = SingMaze
CONFIG  += console
CONFIG  -= app_bundle

INCLUDEPATH += ../../core/

SOURCES += \
    main.cpp \
    SingMazeMain.cpp \
    models/MazeProject.cpp \
    models/TimeMapModel.cpp \
    models/MazeBuffer.cpp \
    views/MazeView.cpp \
    models/ContourModel.cpp \
    views/ProjectDialog.cpp \
    controllers/ProjectFactory.cpp \
    controllers/ContourEditCommand.cpp \
    models/conf/DisplayConf.cpp \
    views/WaveformView.cpp \
    models/MazeContext.cpp

HEADERS  += SingMazeMain.h \
    models/MazeProject.h \
    models/TimeMapModel.h \
    models/MazeBuffer.h \
    views/MazeView.h \
    models/ContourModel.h \
    views/ProjectDialog.h \
    controllers/ProjectFactory.h \
    controllers/ContourEditCommand.h \
    models/conf/DisplayConf.h \
    views/WaveformView.h \
    models/MazeContext.h

FORMS    += SingMazeMain.ui \
    views/ProjectDialog.ui

include(../StandApps.pri)
