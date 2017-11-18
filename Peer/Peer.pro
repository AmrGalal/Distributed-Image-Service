#-------------------------------------------------
#
# Project created by QtCreator 2017-11-15T14:38:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Peer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../Message.cc \
    ../Socket.cc

HEADERS  += mainwindow.h \
    ../Message.h \
    ../Socket.h

FORMS    += mainwindow.ui
