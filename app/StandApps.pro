TEMPLATE = subdirs

SUBDIRS += \
    WorldImageGenerator/WorldImageGenerator.pro \
    SimpleSpecgram

Release:PRE_TARGETDEPS = ../lib/stand.lib
Debug:PRE_TARGETDEPS = ../lib/standd.lib
