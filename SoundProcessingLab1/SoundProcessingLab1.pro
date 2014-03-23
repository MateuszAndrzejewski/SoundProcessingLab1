#-------------------------------------------------
#
# Project created by QtCreator 2014-03-15T16:34:18
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SoundProcessingLab1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    utils.cpp \
    wavfile.cpp

HEADERS  += mainwindow.h \
    wavfile.h \
    utils.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
