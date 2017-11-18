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
    ../Message.cc \
    ../Socket.cc \
    user.cpp

HEADERS  += mainwindow.h \
    ../Message.h \
    ../Socket.h \
    user.h

FORMS    += mainwindow.ui
