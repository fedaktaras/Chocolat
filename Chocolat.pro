#-------------------------------------------------
#
# Project created by QtCreator 2016-12-16T00:58:27
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chocolat
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    new_sell.cpp \
    add_new_product.cpp \
    add_new_type.cpp \
    new_arrival.cpp

HEADERS  += mainwindow.h \
    new_sell.h \
    add_new_product.h \
    add_new_type.h \
    new_arrival.h

FORMS    += mainwindow.ui \
    new_sell.ui \
    add_new_product.ui \
    add_new_type.ui \
    new_arrival.ui
