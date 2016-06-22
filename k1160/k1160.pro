#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T10:03:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = k1160
TEMPLATE = app

INCLUDEPATH += HnGui

include(HnGui/HnGui.pri)

SOURCES += main.cpp \
    hnwindow.cpp \
    hnapp.cpp \
    hnloginform.cpp \
    hnmainform.cpp \
    hnselfcheckform.cpp

HEADERS  += \
    hnwindow.h \
    hnapp.h \
    hnloginform.h \
    hnmainform.h \
    hnselfcheckform.h

FORMS    += \
    hnloginform.ui \
    hnmainform.ui \
    hnselfcheckform.ui
