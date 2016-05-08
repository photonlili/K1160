#include "hncloudform.h"

HNCloudForm::HNCloudForm(QWidget *parent) :
    QWidget(parent)
{
    btnBack = new HNPushButton(this);
    btnDelete = new HNPushButton(this);
    btnSync = new HNPushButton(this);
    btnRefresh = new HNPushButton(this);

    labelTitle = new QLabel(this);
    treeWidget = new HNTreeWidget(this);

    connect(HNClientInstance(this), SIGNAL(signalLogined()),
            this, SLOT(slotSendQueryRoot()));

    InitOCX();
}

void HNCloudForm::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setGeometry(108,100,916,667);
    this->setStyleSheet("HNCloudForm{image:url(:/images/bk/bk_net.png)}""HNCloudForm{background-color:transparent;}");

    int x0 = 400;
    int y0 = 588;

    btnBack ->setFlat(true);
    btnBack->setFocusPolicy(Qt::NoFocus);
    btnBack->setGeometry(729, y0,108,44);
    //btnBack->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_down_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_down_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_down_press.png);}");
    btnBack->iconTable().initNormal(":/images/bt/bt_down_normal.png",
                                    ":/images/bt/bt_down_press.png");

    labelTitle->setGeometry(28,5,111,36);
    labelTitle->setText("云服务");
    labelTitle->setStyleSheet("QLabel{background-color:transparent;font-size:19px}");

    treeWidget->setGeometry(38, 41, 837, 526);

}

void HNCloudForm::slotSendQueryRoot()
{
    treeWidget->query("htp://");
}
