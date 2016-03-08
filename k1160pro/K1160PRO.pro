#-------------------------------------------------
#
# Project created by QtCreator 2015-03-02T09:17:53
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT       += sql
QT       += network
QT       += printsupport

CONFIG += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport serialport
greaterThan(QT_MAJOR_VERSION, 4): CONFIG -= serialport

TARGET = K1160PRO
TEMPLATE = app
TRANSLATIONS += en.ts zh_CN.ts

target.path += /DWINFile

INSTALLS += target

#QMAKE_LIBS += -lsyszuxpinyin
INCLUDEPATH += . \
    ./wifi \
    ./serialport

#INCLUDEPATH +=  /opt/Hanon/k1160/K1160PRO/wifi
#INCLUDEPATH += .
SOURCES += main.cpp\
        mainwindow.cpp \
    qcheckfrom.cpp \
    qmainscreen.cpp \
    qmlabel.cpp \
    qautotest.cpp \
    qpicifrom.cpp \
    qautotestaprocessform.cpp \
    qmanualtestform.cpp \
    qcleanform.cpp \
    qdatafrom.cpp \
    qprinterform.cpp \
    qsettingmethodform.cpp \
    qsettingmachineform.cpp \
    qsettingcleanform.cpp \
    qsettingcalibrationform.cpp \
    qsettingnetform.cpp \
    qsettingdebugform.cpp \
    qsettinguserform.cpp \
    qsettingoriginsform.cpp \
    qhelpform.cpp \
    quserform.cpp \
    qcloudform.cpp \
    qlistgui.cpp \
    readxmlconfig.cpp \
    Serial/posix_qextserialport.cpp \
    Serial/qextserialbase.cpp \
    Serial/qserialprotcol.cpp \
    qdatabasequery.cpp \
    NetSource/NetControl.cpp \
    NetSource/simplenetwork.cpp \
    qcalbase.cpp \
    qcustom/qcustomplot.cpp \
    qinputtool.cpp \
    wifi/qcheaderview.cpp \
    wifi/qcomponent.cpp \
    wifi/qcstandarditemmodel.cpp \
    wifi/qctableview.cpp \
    wifi/qtankpublic.cpp \
    wifi/qwifimanager.cpp \
    wifi/qwifimodel.cpp \
    wifi/qwifipassform.cpp \
    wifi/qwifiview.cpp \
    wifi/qwifiwidget.cpp \
    qsqlquerycheckboxmodel.cpp \
    wifi/qcdialog.cpp \
    serialport/qtankserialmessage.cpp \
    serialport/qtankserialport.cpp

HEADERS  += mainwindow.h \
    qcheckfrom.h \
    qmainscreen.h \
    qmlabel.h \
    qautotest.h \
    qpicifrom.h \
    qautotestaprocessform.h \
    DataDef.h \
    qmanualtestform.h \
    qcleanform.h \
    qdatafrom.h \
    qprinterform.h \
    qsettingmethodform.h \
    qsettingmachineform.h \
    qsettingcleanform.h \
    qsettingcalibrationform.h \
    qsettingnetform.h \
    qsettingdebugform.h \
    qsettinguserform.h \
    qsettingoriginsform.h \
    qhelpform.h \
    quserform.h \
    qcloudform.h \
    qlistgui.h \
    readxmlconfig.h \
    Serial/posix_qextserialport.h \
    Serial/qextserialbase.h \
    Serial/qserialprotcol.h \
    qdatabasequery.h \
    NetSource/NetControl.h \
    NetSource/NetDataCode.h \
    NetSource/NetErrCode.h \
    NetSource/simplenetwork.h \
    qcalbase.h \
    #syspinyin/syszuxim.h \
    #syspinyin/syszuxpinyin.h
    qcustom/qcustomplot.h \
    qinputtool.h \
    wifi/qcheaderview.h \
    wifi/qcomponent.h \
    wifi/qcstandarditemmodel.h \
    wifi/qctableview.h \
    wifi/qtankdefine.h \
    wifi/qtankgui.h \
    wifi/qtanklinux.h \
    wifi/qtankpublic.h \
    wifi/qwifimanager.h \
    wifi/qwifimodel.h \
    wifi/qwifipassform.h \
    wifi/qwifiview.h \
    wifi/qwifiwidget.h \
    qsqlquerycheckboxmodel.h \
    wifi/qcdialog.h \
    serialport/qtankserialmessage.h \
    serialport/qtankserialport.h

FORMS    += mainwindow.ui \
    qcheckfrom.ui \
    qmainscreen.ui \
    qautotest.ui \
    qpicifrom.ui \
    qautotestaprocessform.ui \
    qmanualtestform.ui \
    qcleanform.ui \
    qdatafrom.ui \
    qprinterform.ui \
    qsettingmethodform.ui \
    qsettingmachineform.ui \
    qsettingcleanform.ui \
    qsettingcalibrationform.ui \
    qsettingnetform.ui \
    qsettingdebugform.ui \
    qsettinguserform.ui \
    qsettingoriginsform.ui \
    qhelpform.ui \
    quserform.ui \
    qcloudform.ui \
    #syszuxpinyin.ui
    qinputtool.ui \
    wifi/qctableview.ui \
    wifi/qwifipassform.ui \
    wifi/qwifiview.ui \
    wifi/qwifiwidget.ui \
    wifi/qcdialog.ui

RESOURCES += \
   rc01.qrc