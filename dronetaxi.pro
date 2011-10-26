#-------------------------------------------------
#
# Project created by QtCreator 2010-10-12T20:45:34
#
#-------------------------------------------------

QT       += core gui network
CONFIG += debug
TARGET = dronetaxi
TEMPLATE = app

SOURCES += main.cpp\
    dronecontrol.cpp \
    navdata.cpp \
    video.cpp \
    videoprocessor.cpp \
    gauge.cpp \
    gaugelabel.cpp \
    gaugehorizon.cpp \
    mainwindow.cpp \
    paddetection.cpp \
    gamesettingsdialog.cpp \
    gamemode.cpp \
    gamemodedronetaxi.cpp \
    gamemoderace.cpp \
    gamemodefreeflight.cpp \
    moresettingsdialog.cpp \
    helpdialog.cpp \
    intro.cpp \
    ARToolkitPlus/src/TrackerSingleMarker.cpp \
    ARToolkitPlus/src/Camera.cpp \
    ARToolkitPlus/src/Tracker.cpp \
    ARToolkitPlus/src/TrackerMultiMarker.cpp \
    ARToolkitPlus/src/core/arBitFieldPattern.cpp \
    ARToolkitPlus/src/core/arMultiActivate.cpp \
    ARToolkitPlus/src/core/arDetectMarker.cpp \
    ARToolkitPlus/src/core/arMultiGetTransMat.cpp \
    ARToolkitPlus/src/core/arDetectMarker2.cpp \
    ARToolkitPlus/src/core/arMultiGetTransMatHull.cpp \
    ARToolkitPlus/src/core/arGetCode.cpp \
    ARToolkitPlus/src/core/arMultiReadConfigFile.cpp \
    ARToolkitPlus/src/core/arGetInitRot2.cpp \
    ARToolkitPlus/src/core/arUtil.cpp \
    ARToolkitPlus/src/core/arGetMarkerInfo.cpp \
    ARToolkitPlus/src/core/mPCA.cpp \
    ARToolkitPlus/src/core/arGetTransMat.cpp \
    ARToolkitPlus/src/core/matrix.cpp \
    ARToolkitPlus/src/core/arGetTransMat2.cpp \
    ARToolkitPlus/src/core/paramDecomp.cpp \
    ARToolkitPlus/src/core/arGetTransMat3.cpp \
    ARToolkitPlus/src/core/paramDistortion.cpp \
    ARToolkitPlus/src/core/arGetTransMatCont.cpp \
    ARToolkitPlus/src/core/rppGetTransMat.cpp \
    ARToolkitPlus/src/core/arLabeling.cpp \
    ARToolkitPlus/src/core/rppMultiGetTransMat.cpp \
    ARToolkitPlus/src/core/vector.cpp \
    ARToolkitPlus/src/extra/BCH.cpp \
    ARToolkitPlus/src/extra/Hull.cpp \
    ARToolkitPlus/src/librpp/rpp.cpp \
    ARToolkitPlus/src/librpp/rpp_svd.cpp \
    ARToolkitPlus/src/librpp/arGetInitRot2Sub.cpp \
    ARToolkitPlus/src/librpp/librpp.cpp \
    ARToolkitPlus/src/librpp/rpp_vecmat.cpp \
    ARToolkitPlus/src/librpp/rpp_quintic.cpp


INCLUDEPATH += ARToolkitPlus/include

HEADERS  +=  dronecontrol.h \
    navdata.h \
    navdata_ardrone.h \
    videoprocessor.h \
    video.h \
    vlib.h \
    gauge.h \
    gaugelabel.h \
    gaugehorizon.h \
    mainwindow.h \
    paddetection.h \
    gamesettingsdialog.h \
    gamemode.h \
    gamemodedronetaxi.h \
    gamemoderace.h \
    gamemodefreeflight.h \
    moresettingsdialog.h \
    helpdialog.h \
    intro.h

FORMS += mainwindow.ui \
    gamesettingsdialog.ui \
    moresettingsdialog.ui \
    helpdialog.ui

OTHER_FILES += \
    debian/changelog \
    debian/compat \
    debian/control \
    debian/copyright \
    debian/README \
    debian/rules \
    dronetaxi.desktop \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    data/dronetaxi.png \
    README

RESOURCES += \
    dronteaxi_resources.qrc

contains(MEEGO_EDITION,harmattan) {
    target.path = /opt/dronetaxi/bin
    desktop.files = dronetaxi.desktop
    desktop.path = /usr/share/applications
    icon.files = dronetaxi80x80.png
    icon.path = /usr/share/icons/hicolor/80x80/apps
    config.files = no_distortion.cal
    config.path = /opt/dronetaxi/bin
    INSTALLS += target desktop icon config
}
