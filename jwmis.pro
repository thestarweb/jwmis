#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T20:49:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jwmis
TEMPLATE = app


SOURCES += main.cpp\
        starjwmis.cpp \
    network/http.cpp \
    ui/login.cpp

HEADERS  += starjwmis.h \
    network/http.h \
    ui/login.h
