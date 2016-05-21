#-------------------------------------------------
#
# Project created by QtCreator 2016-05-13T13:25:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serverui
TEMPLATE = app


SOURCES +=\
        mainwindow.cpp \
    main.cpp \
    audioserver.cpp \
    videoserver.cpp \
    AudioInterface.cpp \
    videoupdater.cpp

HEADERS  += mainwindow.h \
    audioserver.h \
    videoserver.h \
    AudioInterface.h \
    videoupdater.h

FORMS    +=

QMAKE_CXXFLAGS = -std=c++11
LIBS += -pthread -lasound

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv
