#include "hnprogressdialog.h"
#include "ui_hnprogressdialog.h"
#include "HNDefine.h"

HNProgressDialog::HNProgressDialog(QWidget *parent) :
    HNDialog(parent),
    ui(new Ui::HNProgressDialog)
{
    ui->setupUi(this);
    bar = ui->widgetBar;
    connect(ui->btnCancel, SIGNAL(clicked()),
            this, SLOT(reject()));
    setFixedWidth(260);
    bar->setRange(0, 100);
    bar->setValue(0);
}

HNProgressDialog::~HNProgressDialog()
{
    delete ui;
}

void HNProgressDialog::initAll()
{
    bar->setRange(0, 100);
    bar->setValue(0);
}

void HNProgressDialog::setRange(int min, int max)
{
    bar->setRange(min, max);
}

void HNProgressDialog::setContent(QString content)
{
    ui->label->setText(content);
}

void HNProgressDialog::setValue(int value)
{
    bar->setValue(value);
}

