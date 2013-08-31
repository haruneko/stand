STAND_UPDIR = $${OUT_PWD}$${STAND_RISEUP}

CONFIG(debug, debug|release) {
    STAND_BUILDDIR = $${STAND_UPDIR}/debug/$${TARGET}
    STAND_LIBDIR   = $${STAND_UPDIR}/debug/libs
} else {
    STAND_BUILDDIR = $${STAND_UPDIR}/release/$${TARGET}
    STAND_LIBDIR   = $${STAND_UPDIR}/release/libs
}

CONFIG(app) {
    DESTDIR = $${STAND_BUILDDIR}
} else {
    DESTDIR = $${STAND_LIBDIR}
}

OBJECTS_DIR = $${STAND_BUILDDIR}/.obj
MOC_DIR     = $${STAND_BUILDDIR}/.moc
RCC_DIR     = $${STAND_BUILDDIR}/.rcc
UI_DIR      = $${STAND_BUILDDIR}/.ui
