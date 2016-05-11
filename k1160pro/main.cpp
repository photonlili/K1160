#include "mainwindow.h"
#include "qmainscreen.h"
#include "qpicifrom.h"
#include "qautotest.h"
#include "qautotestaprocessform.h"
#include "qmanualtestform.h"
#include "qcleanform.h"
#include "qdatafrom.h"
#include "qprinterform.h"
#include "qsettingmethodform.h"
#include "qsettingmachineform.h"
#include "qsettingcleanform.h"
#include "qsettingcalibrationform.h"
#include "qsettingnetform.h"
#include "qsettingdebugform.h"
#include "qsettinguserform.h"
#include "qsettingoriginsform.h"
#include "qhelpform.h"
#include "quserform.h"
#include "qcloudform.h"
#include "qinputtool.h"
#include "hnwindow.h"
#include "QWSServer"
#include <QApplication>
#include <QTextCodec>
#include <QFontDatabase>
#include "hnapp.h"
#include "hntreewidget.h"
#include "hnlocaldbdialog.h"
#include "hnprogressdialog.h"

int main(int argc, char *argv[])
{
    //Q_INIT_RESOURCE(rc01);
    HNApp a(argc, argv);

    QInputTool::Instance()->Init("control", "brown", 10, 10);
    QInputTool::Instance()->hide();

    QWidget w;

#ifdef _MIPS_LINUX_ENV_
    w.setFixedSize(1024, 768);
    w.setWindowFlags(Qt::FramelessWindowHint|w.windowFlags());
    //keyboard
    //QWSInputMethod* im = new SyszuxIM;
    //QWSServer::setCurrentInputMethod(im);
#else
    w.setFixedSize(1024, 768);

#endif
    QVBoxLayout l;
    l.setMargin(0);
    w.setLayout(&l);

    //MainWindow m;
    //l.addWidget(&m);

    w.show();

    QTableWidget w15;
    l.addWidget(&w15);
    w15.setRowCount(4);
    w15.setColumnCount(10);

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            QTableWidgetItem* item = new QTableWidgetItem(QString("%1,%2").arg(i).arg(j));
            w15.setItem(i, j, item);
            w15.setColumnWidth(j, 60);
        }
    }

    w15.horizontalHeader()->hide();
    w15.setAlternatingRowColors(true);
    w15.setColumnHidden(4, true);
    w15.setSpan(0, 6, 4, 1);
    w15.setSpan(1, 7, 1, 3);
    w15.setSpan(0, 1, 4, 4);


    //for(int j = 0; j < 10; j++)
        //pline() << w15.model()->headerData(j, Qt::Horizontal).toString();

    //pline() << w15.columnSpan(0, 3);

    HNReport r;
    r.createSampleReport("aaa", "bbb", "CCC", &w15);
    r.exportPdf("aDDRSpan.pdf");

    return a.exec();
}


