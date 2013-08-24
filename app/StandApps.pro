TEMPLATE = subdirs

SUBDIRS += \
    WorldImageGenerator/WorldImageGenerator.pro \
    SimpleSpecgram \
    SimpleSequenceView \
    SingMaze

Release:PRE_TARGETDEPS += ../lib/stand.lib
Debug:PRE_TARGETDEPS += ../lib/standd.lib
