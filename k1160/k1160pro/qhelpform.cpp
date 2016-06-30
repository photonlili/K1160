#include "qhelpform.h"
#include "ui_qhelpform.h"
#include "version.h"
#include "hnserialport.h"

QHelpForm::QHelpForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QHelpForm)
{
    ui->setupUi(this);
    InitOCX();

    ui->lbVer->setGeometry(640,540,78, 29);
    ui->lbSerial->setGeometry(640,580,235, 29);

    ui->lbVer->setText(VER_FILEVERSION_STR);
    QSettings set;
    QString serial = set.value("Device/DeviceNo").toString();
    qDebug() << serial << set.fileName();
    ui->lbSerial->setText(serial);
}

QHelpForm::~QHelpForm()
{
    delete ui;
}


void QHelpForm::InitOCX()
{
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setGeometry(108,100,916,667);
    this->setStyleSheet("QWidget#HelpWidget{image:url(./skin/default/bk_help.png)}""QHelpForm{background-color:transparent;}");
}

void QHelpForm::InitSings()
{

}

void QHelpForm::AnalysisData(QByteArray pData)
{
}
