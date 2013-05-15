TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
            Stand.pro \
            test\dsp\seem\test_PlatinumSeem.pro \
            test\dsp\seem\test_StarSeem.pro \
            test\dsp\ffem\test_DioFfem.pro \
            test\dsp\world\test_ResidualExtractor.pro \
            app/WorldImageGenerator

