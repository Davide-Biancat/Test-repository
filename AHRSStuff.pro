#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T08:54:54
#
#-------------------------------------------------

QT       += core openglwidgets gui serialport
CONFIG   += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        arduinoreader.cpp \
        glwidget.cpp \
        logo.cpp \
        worker.cpp \
        libs/QCustomPlot/qcustomplot.cpp \
        quaternion.cpp \
        sensorsimulator.cpp

INCLUDEPATH += "$$_PRO_FILE_PWD_/libs/QCustomPlot"

HEADERS  += mainwindow.h \
    arduinoreader.h \
    libs/QCustomPlot/qcustomplot.h \
    glwidget.h \
    logo.h \
    worker.h \
    quaternion.h \
    sensorsimulator.h \
    math_helper.h

FORMS    += mainwindow.ui
