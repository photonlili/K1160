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

#include <QApplication>
#include <QTextCodec>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    //Q_INIT_RESOURCE(rc01);
    QApplication a(argc, argv);
#ifdef _MIPS_LINUX_ENV_
    QFontDatabase db;
    int fontId = db.addApplicationFont("/usr/lib/fonts/wenquanyi.ttf");
    QString wenquanyi = db.applicationFontFamilies ( fontId ).at(0);
    QFont font(wenquanyi,11);

    QApplication::setFont(font);

    //keyboard
    //QWSInputMethod* im = new SyszuxIM;
    //QWSServer::setCurrentInputMethod(im);
#endif
    MainWindow w;
#ifdef _MIPS_LINUX_ENV_
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
#endif
    QInputTool::Instance()->Init("control", "brown", 10, 10);
    QInputTool::Instance()->hide();
    QApplication::setOrganizationName("Hanon");
    QApplication::setOrganizationDomain("hanon.com");  // 专为Mac OS X 准备的
    QApplication::setApplicationName("K1160");
    //QMainScreen w1;
    //QAutoTest w;
    //QPiciFrom w;
    //QAutoTestaProcessForm w;
    //QManualTestForm w;
    //QCleanForm w;
    //QDataFrom w;
    //QPrinterForm w;
    //QSettingMethodForm w;
    //QSettingMachineForm w;
    //QSettingCleanForm w;
    //QSettingCalibrationForm w;
    //QSettingNetForm w;
    //QSettingDebugForm w;
    //QSettingUserForm w;
    //QSettingOriginsForm w;
    //QHelpForm w;
    //QUserForm w;
    //QCloudForm w;
    w.show();

    return a.exec();
}


