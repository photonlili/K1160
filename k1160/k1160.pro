#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T10:03:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = k1160
TEMPLATE = app

INCLUDEPATH += HnGui k1160pro

include(HnGui/HnGui.pri)
include(k1160pro/k1160pro.pri)

QT_KIT = $$(QKIT)

message($${QT_KIT} $$(QKIT) DEFINED)

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

target.path += /HNApp

INSTALLS += target

TRANSLATIONS = HNLang/zh_CN.ts \
	HNLang/en_US.ts

CODECFORTR = UTF-8

SOURCES += main.cpp \
    hnapp.cpp \
    hnloginform.cpp \
    hnmainform.cpp \
    hnselfcheckform.cpp \
    hnmsgbox.cpp \
    hnwindow.cpp \
    HNInput.cpp \
    hnmanageethenetwidget.cpp \
    hnmanageuserwidget.cpp \
    hncloudform.cpp \
    hnlocaldbdialog.cpp \
    hnprogressdialog.cpp \
    hnwifimodel.cpp \
    hnwifiview.cpp \
    hnwifiwidget.cpp \
    hnpassworddialog.cpp \
    hnuserinfomodel.cpp \
    hnuserinfoview.cpp \
    hnuserinfowidget.cpp \
    hnsampledatawidget.cpp \
    hnsuyuanform.cpp \
    hnprintinfodialog.cpp

HEADERS  += \
    hnapp.h \
    hnloginform.h \
    hnmainform.h \
    hnselfcheckform.h \
    hnmsgbox.h \
    hnwindow.h \
    HNInput.h \
    hnmanageethenetwidget.h \
    hnmanageuserwidget.h \
    hncloudform.h \
    hnlocaldbdialog.h \
    hnprogressdialog.h \
    hnwifimodel.h \
    hnwifiview.h \
    hnwifiwidget.h \
    hnpassworddialog.h \
    hnuserinfomodel.h \
    hnuserinfoview.h \
    hnuserinfowidget.h \
    hnsampledatawidget.h \
    hnsuyuanform.h \
    hnprintinfodialog.h

FORMS    += \
    hnloginform.ui \
    hnmainform.ui \
    hnselfcheckform.ui \
    hnmsgbox.ui \
    hnwindow.ui \
    HNInput.ui \
    hnmanageethenetwidget.ui \
    hnmanageuserwidget.ui \
    hnprogressdialog.ui \
    hnwifiview.ui \
    hnwifiwidget.ui \
    hnpassworddialog.ui \
    hnuserinfoview.ui \
    hnuserinfowidget.ui \
    hnsampledatawidget.ui \
    hnprintinfodialog.ui

OTHER_FILES += \
    k1160.pro.user
