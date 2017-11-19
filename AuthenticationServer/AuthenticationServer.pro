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
    user.cpp \
    ../message.cc \
    ../socket.cc

HEADERS  += mainwindow.h \
    user.h \
    ../message.h \
    ../socket.h

FORMS    += mainwindow.ui
