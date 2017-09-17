#include "qqtselfcheckform.h"
#include "ui_qqtselfcheckform.h"
#include "qqtobjectfactory.h"

QQTSelfCheckForm::QQTSelfCheckForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QQTSelfCheckForm)
{
    ui->setupUi(this);

    QQTObjectFactory::registerObject(this);
}

QQTSelfCheckForm::~QQTSelfCheckForm()
{
    delete ui;
}
