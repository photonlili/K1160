#include "hnmainform.h"
#include "ui_hnmainform.h"
#include "hnobjectfactory.h"

HNMainForm::HNMainForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNMainForm)
{
    ui->setupUi(this);

    HNObjectFactory::registerObject(this);

    ui->label_appname->setForegroundRole(QPalette::BrightText);
    ui->label_time->setText(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss"));
    ui->label_time->setForegroundRole(QPalette::BrightText);
    ui->label_user->setForegroundRole(QPalette::BrightText);
    ui->label->setForegroundRole(QPalette::BrightText);

    ui->widget_title->setFixedHeight(58);
    ui->widget_logo->setFixedWidth(108);

    for(int i = 0; i < 6; i++)
        ui->tabWidget->setTabText(i , "");

    HNTabBar* bar = (HNTabBar*)ui->tabWidget->cTabBar();
    bar->setTabPixmap(0, "./skin/default/bt_main_normal.png", "./skin/default/bt_main_press.png");
    bar->setTabPixmap(1, "./skin/default/bt_main2_normal.png", "./skin/default/bt_main2_press.png");
    bar->setTabPixmap(2, "./skin/default/bt_set_normal.png", "./skin/default/bt_set_press.png");
    bar->setTabPixmap(3, "./skin/default/bt_help_normal.png", "./skin/default/bt_help_press.png");
    bar->setTabPixmap(4, "./skin/default/bt_user_normal.png", "./skin/default/bt_user_press.png");
    bar->setTabPixmap(5, "./skin/default/bt_server_normal.png", "./skin/default/bt_server_press.png");

    ui->tabWidget->cTabBar()->installEventFilter(this);
}

HNMainForm::~HNMainForm()
{
    delete ui;
}

void HNMainForm::init()
{
    setUser();
    setTheme();
    setHead();
}

void HNMainForm::setUser()
{
    ui->label_user->setText(gUserName);
}

void HNMainForm::setHead()
{
    QSettings setting;
    QString picName = setting.value(QString("/%1/HeadPic").arg(gUserName)).toString();
    if(picName.isEmpty())
        picName = "head1";
    ui->widget_pic->setPixmap(QString("./skin/default/bk_%1_normal.png").arg(picName));
    ui->widget_pic->update();
}


void HNMainForm::setTheme()
{
    QSettings setting;
    QString themeName = setting.value(QString("/%1/ThemePic").arg(gUserName)).toString();
    if(themeName.isEmpty())
        themeName = "theme1";

    //pline() << QDateTime::currentDateTime();
    QFile styleFile(QString("./%1/theme.qss").arg(themeName));
    styleFile.open(QIODevice::ReadOnly);
    QString styleString(styleFile.readAll());;
    setStyleSheet(styleString);
    styleFile.close();
    //pline() << QDateTime::currentDateTime();
}

void HNMainForm::setLanguage()
{

}

void HNMainForm::wifiConnected()
{
    ui->widget_wifi->setPixmap("./skin/default/bk_wifi_connected.png");
    ui->widget_wifi->update();
}

void HNMainForm::wifiDisConnected()
{
    ui->widget_wifi->setPixmap("./skin/default/bk_wifi_unconnected.png");
    ui->widget_wifi->update();
}

void HNMainForm::wifiConnecting()
{
    ui->widget_wifi->setPixmap("./skin/default/bk_wifi_connecting.png");
    ui->widget_wifi->update();
}

bool HNMainForm::eventFilter(QObject *obj, QEvent *e)
{
    return QWidget::eventFilter(obj, e);
}
