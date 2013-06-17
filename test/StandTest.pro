TEMPLATE = subdirs

SUBDIRS += \
        dsp\synthesis\test_VocoderRenderer.pro \
        dsp\synthesis\test_WorldSynthesis.pro \
        dsp\seem\test_PlatinumSeem.pro \
        dsp\seem\test_StarSeem.pro \
        dsp\ffem\test_DioFfem.pro \
        dsp\world\test_ResidualExtractor.pro \
    utility/test_Utility

Release:PRE_TARGETDEPS = ../lib/Stand.lib
Debug:PRE_TARGETDEPS = ../lib/Standd.lib
Release:PRE_TARGETDEPS = ../lib/StandGui.lib
Debug:PRE_TARGETDEPS = ../lib/StandGuid.lib
