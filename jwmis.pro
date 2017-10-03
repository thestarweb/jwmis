#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T20:49:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT+=network


TARGET = jwmis
TEMPLATE = app


SOURCES += main.cpp\
        starjwmis.cpp \
    network/http.cpp \
    ui/login.cpp \
    ui/menu.cpp \
    network/http_response.cpp \
    ui/yzm.cpp \
    network/jwweb_net.cpp \
    ui/my_info.cpp \
    ui/cjfb.cpp

HEADERS  += starjwmis.h \
    network/http.h \
    ui/login.h \
    ui/menu.h \
    network/http_response.h \
    ui/yzm.h \
    network/jwweb_net.h \
    ui/my_info.h \
    ui/cjfb.h
