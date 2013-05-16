TEMPLATE = subdirs

SUBDIRS += \
        WorldImageGenerator/WorldImageGenerator.pro

Release:PRE_TARGETDEPS = ../../stand.lib
Debug:PRE_TARGETDEPS = ../../standd.lib
