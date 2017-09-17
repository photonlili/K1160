#include "qqtmanageuserwidget.h"
#include "ui_qqtmanageuserwidget.h"

QQTManageUserWidget::QQTManageUserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQTManageUserWidget)
{
    ui->setupUi(this);
    ui->tbvUserInfo->addMap(ui->lbName, Auth_Name, "text");
    ui->tbvUserInfo->addMap(ui->lbPwd, Auth_Passwd, "text");
    ui->tbvUserInfo->addMap(ui->lbAuth, Auth_Authrity, "text");
    ui->tbvUserInfo->addMap(ui->lbCreater, Auth_Creater, "text");
    ui->tbvUserInfo->addMap(ui->lbCreateTime, Auth_CreateTime, "text");
    ui->tbvUserInfo->addMap(ui->lbComment, Auth_Comment, "text");
    connect(ui->tbvUserInfo->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)),
            ui->tbvUserInfo, SLOT(updateMap()));
    ui->tbvUserInfo->refresh();


}

QQTManageUserWidget::~QQTManageUserWidget()
{
    delete ui;
}

void QQTManageUserWidget::on_btnNewUser_clicked()
{

}

void QQTManageUserWidget::on_btnDelUser_clicked()
{

}
