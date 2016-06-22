#include "hnselfcheckform.h"
#include "ui_hnselfcheckform.h"

HNSelfCheckForm::HNSelfCheckForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNSelfCheckForm)
{
    ui->setupUi(this);
}

HNSelfCheckForm::~HNSelfCheckForm()
{
    delete ui;
}

void HNSelfCheckForm::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
