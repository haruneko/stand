TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
            core/StandCore.pro \
            app/StandApps.pro \
            test/StandTest.pro

app/StandApps.pro.depends = StandCore.pro
test/StandTest.pro.depends = StandCore.pro
