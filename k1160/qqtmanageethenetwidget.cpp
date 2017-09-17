#include "qqtmanageethenetwidget.h"
#include "ui_qqtmanageethenetwidget.h"

QQTManageEthenetWidget::QQTManageEthenetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQTManageEthenetWidget)
{
    ui->setupUi(this);
    connect(QQTEthenetManager::Instance(), SIGNAL(sigConnected()), this, SLOT(wifiConnected()));
    connect(QQTEthenetManager::Instance(), SIGNAL(sigDisConnected()), this, SLOT(wifiDisConnected()));
    connect(QQTEthenetManager::Instance(), SIGNAL(sigLanConnected()), this, SLOT(netChanged()));
    connect(QQTEthenetManager::Instance(), SIGNAL(sigLanDisConnected()), this, SLOT(netChanged()));
}

QQTManageEthenetWidget::~QQTManageEthenetWidget()
{
    delete ui;
}

void QQTManageEthenetWidget::initAll()
{
    QString ip, mask, gw, dns;
    QQTEthenetManager::Instance()->getAddr(ip, mask, gw, dns);
    ui->lineEdit_ip->setText(ip);
    ui->lineEdit_mask->setText(mask);
    ui->lineEdit_gateway->setText(gw);
    ui->lineEdit_dns->setText(dns);

    QSettings setting;
    int bCheked = false;
    bCheked = setting.value("EnableDHCP").toInt();
    ui->chk_dhcp->setChecked(bCheked);
}

void QQTManageEthenetWidget::netChanged()
{
    QString netName;
    if("Wired Lan" == QQTEthenetManager::Instance()->currentNetName())
    {
        netName = tr("Current:Wired Lan");
        ui->tableView_Wifi->setEnabled(false);
    }
    else
    {
        netName = tr("Current:%1").arg(QQTEthenetManager::Instance()->currentNetName());
        ui->tableView_Wifi->setEnabled(true);
    }
    ui->label->setText(netName);

}

void QQTManageEthenetWidget::wifiConnected()
{

}

void QQTManageEthenetWidget::wifiDisConnected()
{

}

void QQTManageEthenetWidget::on_btn_saveip_clicked()
{
    QQTEthenetManager::Instance()->setAddr(ui->lineEdit_ip->text(), ui->lineEdit_mask->text(),
                                      ui->lineEdit_gateway->text(), ui->lineEdit_dns->text());
    QQTEthenetManager::Instance()->ipconfig();
}

void QQTManageEthenetWidget::on_chk_dhcp_stateChanged(int arg1)
{
    QSettings setting;
    setting.setValue("EnableDHCP", arg1);
    setting.sync();

    bool bChecked = arg1?true:false;
    QQTEthenetManager::Instance()->setDHCP(bChecked);
    ui->lineEdit_ip->setDisabled(bChecked);
    ui->lineEdit_mask->setDisabled(bChecked);
    ui->lineEdit_gateway->setDisabled(bChecked);
    ui->lineEdit_dns->setDisabled(bChecked);
}
