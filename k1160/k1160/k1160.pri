#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T14:08:11
#
#-------------------------------------------------

QT       += core gui network sql

CONFIG += serialport

DEFINES += _TTY_POSIX_

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD

QT_KIT = $$(QKIT)

message($${QT_KIT} Defined in k1160exclusive)

#MIPS __MIPS_LINUX__
#PC64 __LINUX64__

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

SOURCES += \
    $$PWD/qqtselfcheckform.cpp \
    $$PWD/qqtsampledatawidget.cpp \
    $$PWD/qqtprintinfodialog.cpp \
    $$PWD/qqtk1160serialprotocol.cpp

HEADERS  += \
    $$PWD/qqtselfcheckform.h \
    $$PWD/qqtsampledatawidget.h \
    $$PWD/qqtprintinfodialog.h \
    $$PWD/qqtk1160serialprotocol.h

FORMS    += \
    $$PWD/qqtselfcheckform.ui \
    $$PWD/qqtsampledatawidget.ui \
    $$PWD/qqtprintinfodialog.ui

