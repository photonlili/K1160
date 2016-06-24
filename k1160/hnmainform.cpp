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
    ui->label_time->setText(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm"));
    ui->label_time->setForegroundRole(QPalette::BrightText);
    ui->label_user->setForegroundRole(QPalette::BrightText);
    ui->label->setForegroundRole(QPalette::BrightText);

    ui->widget_title->setFixedHeight(60);
    ui->widget_logo->setFixedWidth(108);

    HNTabBar* bar = (HNTabBar*)ui->tabWidget->cTabBar();
    bar->setTabPixmap(0, "./skin/default/bt_main_normal.png", "./skin/default/bt_main_press.png");
    bar->setTabPixmap(1, "./skin/default/bt_main2_normal.png", "./skin/default/bt_main2_press.png");
    bar->setTabPixmap(2, "./skin/default/bt_set_normal.png", "./skin/default/bt_set_press.png");
    bar->setTabPixmap(3, "./skin/default/bt_help_normal.png", "./skin/default/bt_help_press.png");
    bar->setTabPixmap(4, "./skin/default/bt_user_normal.png", "./skin/default/bt_user_press.png");
    bar->setTabPixmap(5, "./skin/default/bt_cloud_normal.png", "./skin/default/bt_cloud_press.png");

    ui->tabWidget->cTabBar()->installEventFilter(this);
}

HNMainForm::~HNMainForm()
{
    delete ui;
}

bool HNMainForm::eventFilter(QObject *obj, QEvent *e)
{
    return QWidget::eventFilter(obj, e);
}
