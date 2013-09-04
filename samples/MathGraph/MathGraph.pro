#-------------------------------------------------
#
# Project created by QtCreator 2013-06-29T03:34:29
#
#-------------------------------------------------

QT       += core gui

include(../../QMathGraph.pri)
MOC_DIR = tmp
OBJECTS_DIR = obj
DEPENDPATH += . ../../src
INCLUDEPATH += . ../../src
TARGET = MathGraph
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
