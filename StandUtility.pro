TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS += \
            Stand.pro \
            app/StandApps.pro \
            test/StandTest.pro

app/StandApps.pro.depends = Stand.pro
test/StandTest.pro.depends = Stand.pro
