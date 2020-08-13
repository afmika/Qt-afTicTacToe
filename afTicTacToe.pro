# Tells build system that project uses Qt Core and Qt GUI modules. 
QT       += core gui 
 
# Prior to Qt 5 widgets were part of Qt GUI module. In Qt 5 we need to add Qt Widgets module. 
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets 
 
# Specifies name of the binary. 
TARGET = afTicTacToe
CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    mainwindow.cpp

HEADERS += \
    TicTacToe.h \
    afCanvasView.h \
    mainwindow.h
