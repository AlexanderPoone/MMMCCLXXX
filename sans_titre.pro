#-------------------------------------------------
#
# Project created by QtCreator 2017-02-18T15:58:41
#
#-------------------------------------------------

QT       += core gui network concurrent testlib charts multimedia multimediawidgets
#webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sans_titre
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
#\
#            UNICODE

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    button.cpp \
    stopbutton.cpp \
    playpausebutton.cpp \
    geniusmanager.cpp \
    gloweffect.cpp \
    ratingbar.cpp \
    albumentry.cpp \
    nextbutton.cpp \
    previousbutton.cpp \
    musiclibrary.cpp \
    tracklistbubble.cpp \
    bulletscreen.cpp \
    winsockserverthread.cpp \
    winsockclientthread.cpp \
    lrchandler.cpp \
    visualisationwidget.cpp \
    wavplayer.cpp \
    wavdeassembler.cpp \
    wavassembler.cpp \
    xyseriesiodevice.cpp \
    videobutton.cpp \
    videodialog.cpp \
    videocentralwidget.cpp \
    videoplayercontrols.cpp \
    videogiantwidget.cpp \
    playlistmodel.cpp


HEADERS  += mainwindow.h \
    button.h \
    stopbutton.h \
    playpausebutton.h \
    geniusmanager.h \
    gloweffect.h \
    ratingbar.h \
    albumentry.h \
    nextbutton.h \
    previousbutton.h \
    musiclibrary.h \
    tracklistbubble.h \
    bulletscreen.h \
    winsockserverthread.h \
    winsockclientthread.h \
    lrchandler.h \
    visualisationwidget.h \
    wavplayer.h \
    wavdeassembler.h \
    wavassembler.h \
    xyseriesiodevice.h \
    videobutton.h \
    videodialog.h \
    videocentralwidget.h \
    videoplayercontrols.h \
    videogiantwidget.h \
    playlistmodel.h

FORMS    += mainwindow.ui \
            mainwindowC.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    res.qrc

#install_it.path = $$OUT_PWD
#install_it.files = $$PWD\*.dll

#INSTALLS += \
#    install_it

QMAKE_POST_LINK += $${QMAKE_COPY} $${PWD}/libeay32.dll $$shadowed($$PWD)/libeay32.dll
QMAKE_POST_LINK += $${QMAKE_COPY} $${PWD}/ssleay32.dll $$shadowed($$PWD)/ssleay32.dll
