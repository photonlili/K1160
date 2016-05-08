#include "hntreeview.h"
#include "ui_hntreeview.h"
#include <QFile>

HNTreeView::HNTreeView(QWidget *parent) :
    QTreeView(parent),
    ui(new Ui::HNTreeView)
{
    ui->setupUi(this);
}

HNTreeView::~HNTreeView()
{
    delete ui;
}
