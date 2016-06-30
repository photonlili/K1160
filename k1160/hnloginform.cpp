#include "hnloginform.h"
#include "ui_hnloginform.h"
#include "hnobjectfactory.h"
#include "hnmsgbox.h"
#include "hngui-qt.h"
#include "HNDefine.h"
#include "hnwindow.h"

HNLoginForm::HNLoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNLoginForm)
{
    ui->setupUi(this);

    ui->widgetLogin->setFixedSize(460, 310);

    ui->labelLogin->setFixedHeight(30);

    ui->widgetMiddle->setFixedHeight(130);
    ui->cbName->setFixedSize(230, 30);
    ui->lePasswd->setFixedSize(230, 30);
    ui->widgetHeader->setFixedSize(24, 30);
    ui->widgetPassword->setFixedSize(24, 30);

    //ui->widgetBottom->setFixedHeight(130);
    ui->btnLogin->setFixedSize(104, 40);

    ui->btnLogin->setStyleSheet("QPushButton{background-color:transparent;background-image: url(./skin/default/bt_login_normal.png)}""QPushButton:hover{background-image: url(./skin/default/bt_login_normal.png);}""QPushButton:pressed{background-image: url(./skin/default/bt_login_press.png);}");


    HNObjectFactory::registerObject(this);

    ui->cbName->clear();
    QSqlQuery query(managerDB);
    query.exec(QString("SELECT * FROM %1").arg(TABLE_USERINFO));

    while (query.next()) {
        ui->cbName->addItem(query.value(Auth_Name).toString());
    }
    query.finish();

}

HNLoginForm::~HNLoginForm()
{
    delete ui;
}

void HNLoginForm::on_btnLogin_clicked()
{
    QSqlQuery query(managerDB);
    query.exec(QString("SELECT * FROM %1 WHERE Name = '%2'")
               .arg(TABLE_USERINFO).arg(ui->cbName->currentText()));

    if (query.next()) {
        gUserName = query.value(Auth_Name).toString();
        gPassword = query.value(Auth_Passwd).toString();
        if(!gPassword.isEmpty() && gPassword == ui->lePasswd->text())
        {
            qDebug("password ok");

            HNWindow* w = (HNWindow*)HNObjectFactory::registedObject("HNWindow");
            w->setMainForm();
        }
        else
        {
            HNMsgBox::warning(this, tr("Password error"));
            //QMsgBox::warning(this, tr("Warning"), tr("Password error"), QMessageBox::Yes);
            qDebug("password error");
        }
    }
    else
    {
        HNMsgBox::warning(this, tr("User name error"));
        //QMsgBox::warning(this, tr("Warning"), tr("User name error"), QMessageBox::Yes);
    }
    query.finish();
}
