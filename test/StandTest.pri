STAND_RISEUP = /../../..
include(../Stand.pri)

win32-msvc {
    LIBS += $${STAND_LIBDIR}/Stand.lib $${STAND_LIBDIR}/StandGui.lib
} else {
    LIBS += -L$${STAND_LIBDIR} -lStand -lStandGui
}
