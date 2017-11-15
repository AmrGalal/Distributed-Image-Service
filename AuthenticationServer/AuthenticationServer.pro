#-------------------------------------------------
#
# Project created by QtCreator 2017-11-15T14:29:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AuthenticationServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Socket.cc \
    Message.cc

HEADERS  += mainwindow.h \
    Socket.h \
    Message.h

FORMS    += mainwindow.ui
