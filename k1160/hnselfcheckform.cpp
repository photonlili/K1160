#include "hnselfcheckform.h"
#include "ui_hnselfcheckform.h"
#include "hnobjectfactory.h"

HNSelfCheckForm::HNSelfCheckForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNSelfCheckForm)
{
    ui->setupUi(this);

    HNObjectFactory::registerObject(this);
}

HNSelfCheckForm::~HNSelfCheckForm()
{
    delete ui;
}
