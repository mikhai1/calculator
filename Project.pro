#-------------------------------------------------
#
# Project created by QtCreator 2017-10-10T23:33:20
#
#-------------------------------------------------

CONFIG += c++14

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    calculate.cpp

HEADERS  += mainwindow.h \
    calculate.h

FORMS    += mainwindow.ui

RESOURCES += resources/resources.qrc

TRANSLATIONS = languages/ru.qph
