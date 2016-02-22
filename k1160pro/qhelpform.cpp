#include "qhelpform.h"
#include "ui_qhelpform.h"

QHelpForm::QHelpForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QHelpForm)
{
    ui->setupUi(this);
    InitOCX();
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
    this->setStyleSheet("QWidget#QHelpForm{image:url(:/images/bk/bk_help.png)}""QHelpForm{background-color:transparent;}");
}

void QHelpForm::InitSings()
{

}
