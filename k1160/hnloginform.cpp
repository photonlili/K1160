#include "hnloginform.h"
#include "ui_hnloginform.h"
#include "hnobjectfactory.h"

HNLoginForm::HNLoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNLoginForm)
{
    ui->setupUi(this);

    HNObjectFactory::registerObject(this);
}

HNLoginForm::~HNLoginForm()
{
    delete ui;
}
