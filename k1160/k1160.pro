#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T10:03:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = k1160
TEMPLATE = app

OBJECTS_DIR = obj
MOC_DIR = moc
RCC_DIR = qrc
UI_DIR = ui_h
DESTDIR = bin

INCLUDEPATH += ../qqtfoundation \
	k1160 \
	k1160pro

include(../qqtfoundation/qqtfoundation.pri)
include(k1160/k1160.pri)
include(k1160pro/k1160pro.pri)

QT_KIT = $$(QKIT)

message($${QT_KIT} Defined in k1160)

DEFINES += _TTY_POSIX_

equals(QT_KIT, MIPS32) {
	QT += multimedia
	DEFINES += __MIPS_LINUX__
} else {
	DEFINES += __LINUX64__
}

CONFIG(debug, debug|release) {
} else {
	DEFINES -= QT_NO_DEBUG_OUTPUT
}

INCLUDEPATH +=  .

target.path += /application

INSTALLS += target

SOURCES += main.cpp\
        $$PWD/qqtapp.cpp \
        $$PWD/qqtloginform.cpp \
        $$PWD/qqtmainform.cpp \
        $$PWD/qqtwindow.cpp \
        $$PWD/qqtmanageethenetwidget.cpp \
        $$PWD/qqtmanageuserwidget.cpp \
        $$PWD/qqtcloudform.cpp \
        $$PWD/qqtlocaldbdialog.cpp \
        $$PWD/qqtprogressdialog.cpp \
        $$PWD/qqtwifiwidget.cpp \
        $$PWD/qqtpassworddialog.cpp \
        $$PWD/qqtuserinfowidget.cpp \
        $$PWD/qqtupgradewidget.cpp \
        $$PWD/qqtsuyuanform.cpp

HEADERS  += \
        $$PWD/qqtapp.h \
        $$PWD/qqtloginform.h \
        $$PWD/qqtmainform.h \
        $$PWD/qqtwindow.h \
        $$PWD/qqtmanageethenetwidget.h \
        $$PWD/qqtmanageuserwidget.h \
        $$PWD/qqtcloudform.h \
        $$PWD/qqtlocaldbdialog.h \
        $$PWD/qqtprogressdialog.h \
        $$PWD/qqtwifiwidget.h \
        $$PWD/qqtpassworddialog.h \
        $$PWD/qqtuserinfowidget.h \
        $$PWD/qqtupgradewidget.h \
        $$PWD/qqtsuyuanform.h

FORMS    += \
        $$PWD/qqtloginform.ui \
        $$PWD/qqtmainform.ui \
        $$PWD/qqtwindow.ui \
        $$PWD/qqtmanageethenetwidget.ui \
        $$PWD/qqtmanageuserwidget.ui \
        $$PWD/qqtprogressdialog.ui \
        $$PWD/qqtwifiwidget.ui \
        $$PWD/qqtuserinfowidget.ui \
        $$PWD/qqtupgradewidget.ui \
        $$PWD/qqtpassworddialog.ui

OTHER_FILES += \
    k1160.pro.user
