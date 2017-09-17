#include "qqtwindow.h"
#include "ui_qqtwindow.h"
#include "qqtobjectfactory.h"
#include "qqtgui-qt.h"
#include "qqtdefine.h"

QQTWindow::QQTWindow(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::QQTWindow)
{
    ui->setupUi(this);

    QQTObjectFactory::registerObject(this);

#ifdef __MIPS_LINUX__
    //这里只要frameless足够
    setWindowFlags(Qt::FramelessWindowHint);
    //控件背景透明，显示设置的图片背景或者下一级背景。
    setAttribute(Qt::WA_TranslucentBackground, true);
#endif
    setFixedSize(1024, 768);
    moveCenter(this);

    QSettings setting;
    int bOpenRights = 1;
    bOpenRights = setting.value("UserRights", bOpenRights).toInt();
    int bSelfCheck = 1;
    bSelfCheck = setting.value("SelfCheck", bSelfCheck).toInt();

    //这里引发跳转的页面不同，页面上控件不同显示不同。
    pline() << bSelfCheck << bOpenRights;
    if(bSelfCheck)
    {
        ui->pageSelfCheck->start();
        setCurrentIndex(0);
        return;
    }
    else if(bOpenRights)
    {
        setCurrentIndex(1);
        return;
    }

    //如果不知道admin的id；设定admin id=0
    QSettings set;
    QString did = set.value("DefaultLogin", 0).toString();

    QSqlQuery query(managerDB);
    if(did == 0)
        query.exec(QString("SELECT * FROM %1 WHERE Name = 'Admin'")
                   .arg(TABLE_USERINFO));
    else
        query.exec(QString("SELECT * FROM %1 WHERE id = '%2'")
                   .arg(TABLE_USERINFO).arg(did));

    if (query.next()) {
        gUserName = query.value(Auth_Name).toString();
        gPassword = query.value(Auth_Passwd).toString();
    }

    query.finish();

    /*
    QString strnameex = "mingcheng";
    QString strtable = "user";
    QStringList linstvalues;
    QDatabasequery* pdataquery = new QDatabasequery(this);
    if(true == pdataquery->opendatabase())
    {
        pdataquery->GetValues(strtable, linstvalues, 1);
        pdataquery->cloesdatabase();
    }

    for(int i = 0; i < linstvalues.count(); i++)
    {
        QString str= linstvalues.at(i);
        ui->cb_username->addItem(str);
    }

    QSettings set;
    int rights = set.value("UserRights", 1).toInt();
    if(0 == rights)
    {
        int d = set.value("DefaultLogin").toInt();
        ui->cb_username->setCurrentIndex(d);
    gPassword = "400618618";
*/
    ui->pageMain->init();
    setCurrentIndex(2);
}

QQTWindow::~QQTWindow()
{
    delete ui;
}

void QQTWindow::setLoginForm()
{
    setCurrentIndex(1);
}

void QQTWindow::setMainForm()
{
    setCurrentIndex(2);
    ui->pageMain->init();
}

void QQTWindow::setSelfCheckForm()
{
    setCurrentIndex(0);
}
