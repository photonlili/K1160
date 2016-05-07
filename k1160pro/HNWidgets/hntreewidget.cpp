#include "hntreewidget.h"
#include "ui_hntreewidget.h"

HNTreeWidget::HNTreeWidget(QWidget *parent) :
    QTreeView(parent),
    ui(new Ui::HNTreeWidget)
{
    ui->setupUi(this);

    m_fs = new HNFileSystem(this);
    m_model = new HNTreeModel(this, m_fs);
    setModel(m_model);
}

HNTreeWidget::~HNTreeWidget()
{
    delete ui;
}

void HNTreeWidget::query(QString path)
{
    m_model->query(path);
}
