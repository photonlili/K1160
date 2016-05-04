#include "hntablewidget.h"
#include "ui_hntablewidget.h"
#include "HNDefine.h"
#include "hngui-qt.h"

HNTableWidget::HNTableWidget(QWidget *parent) :
    HNTableView(parent),
    ui(new Ui::HNTableWidget)
{
    ui->setupUi(this);
    m_db = newDatabaseConn();
    m_model = new HNTableModel(this, m_db);
    setModel(m_model);
}

HNTableWidget::~HNTableWidget()
{
    delete ui;
}

void HNTableWidget::setDB(QString db)
{
    setDatabaseName(m_db, db);
}

void HNTableWidget::setTable(QString table)
{
    m_model->setTable(table);
}

void HNTableWidget::query(QString excp)
{
    m_model->query(excp);
}

void HNTableWidget::delItem(int row)
{
    m_model->removeRow(row);
    m_model->submit();
}

void HNTableWidget::selectedRows(QMap<int, QStringList> &ids)
{
    QModelIndexList l = selectionModel()->selectedRows(0);
    QModelIndex idx;
    foreach (idx, l) {
        QStringList l;
        for(int i = 0; i < m_model->columnCount(); i++)
            l << m_model->index(idx.row(), i).data().toString();
        ids.insert(idx.row(), l);
    }
}
