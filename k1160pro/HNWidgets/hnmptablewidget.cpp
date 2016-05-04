#include "hnmptablewidget.h"
#include "ui_hnmutipagewidget.h"
#include "HNDefine.h"
#include "hngui.h"
#include "hnobjectfactory.h"

HNMPTableWidget::HNMPTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNMPTableWidget)
{
    ui->setupUi(this);

    m_db = newDatabaseConn();

    m_numPerPage = 14;
    selectionMode = QAbstractItemView::MultiSelection;
    altColor = true;
    resizeMode = QHeaderView::ResizeToContents;

    ui->btnJump->setFixedWidth(30);
    ui->btnLeft->setFixedWidth(30);
    ui->btnRight->setFixedWidth(30);
    ui->btnLeftHead->setFixedWidth(30);
    ui->btnRightHead->setFixedWidth(30);
    ui->leNum->setFixedWidth(40);
    ui->btnJump->setHidden(true);
    ui->leNum->setHidden(true);
    ui->btnRightHead->setHidden(true);
    ui->btnRight->setHidden(true);
    ui->btnLeftHead->setHidden(true);
    ui->btnLeft->setHidden(true);

}

HNMPTableWidget::~HNMPTableWidget()
{
    delete ui;
}

void HNMPTableWidget::setDB(QString db)
{
    m_name = db;
    setDatabaseName(m_db, m_name);
}

void HNMPTableWidget::setTable(QString table)
{
    m_table = table;
}

void HNMPTableWidget::query(QString filter)
{
    QSqlQuery query(m_db);
    query.exec(QString("select count(*) from %1").arg(m_table));

    int num = 0;
    if(query.next())
    {
        num = query.value(0).toInt();
        pline() << "record num:" << num;
    }
    query.finish();

    while(ui->stWidgetPage->count())
        ui->stWidgetPage->removeWidget(ui->stWidgetPage->widget(0));

    int pageNum = 0;
    if(num%m_numPerPage>0)
        pageNum = num / m_numPerPage+1;
    else
        pageNum = num / m_numPerPage;

    for(int i = 0; i < pageNum; i++)
    {
        HNTableWidget* page = new HNTableWidget(this);
        page->setDB(m_name);
        page->setTable(m_table);
        page->query(QString("%1 limit %2 offset %3")
                    .arg(filter)
                    .arg(m_numPerPage)
                    .arg(i*m_numPerPage));
        QAbstractItemModel* m_model = page->model();
        for(int i = 0; i < m_model->columnCount(); i++)
            m_model->setHeaderData(
                        i, Qt::Horizontal,
                        m_headerData.value(i, m_model->headerData(i, Qt::Horizontal).toString()));
        page->setSelectionMode(selectionMode);
        page->setAlternatingRowColors(altColor);
        page->horizontalHeader()->setResizeMode(resizeMode);
        for(int i = 0; i < m_model->columnCount(); i++)
            page->horizontalHeader()->setResizeMode(i, m_resizeMode.value(i, resizeMode));
        for(int i = 0; i < m_model->columnCount(); i++)
            page->setColumnWidth(i, m_columnWidth.value(i));
        ui->stWidgetPage->addWidget(page);
    }
}

void HNMPTableWidget::selectedItems(QVector<QStringList> &lid)
{
    for(int i = 0; i < ui->stWidgetPage->count(); i++)
    {
        HNTableWidget* page = (HNTableWidget*)ui->stWidgetPage->widget(i);
        QMap<int, QStringList> ids;
        page->selectedRows(ids);
        QMapIterator<int, QStringList> itor(ids);
        while (itor.hasNext()) {
            itor.next();
            lid.append(itor.value());
        }
    }
}

int HNMPTableWidget::pageNum()
{
    return ui->stWidgetPage->count();
}

int HNMPTableWidget::currentPage()
{
    return ui->stWidgetPage->currentIndex();
}

void HNMPTableWidget::setCurrentPage(int page)
{
    if(page < 1 || page > ui->stWidgetPage->count())
        return;
    ui->stWidgetPage->setCurrentIndex(page-1);
    ui->lbPos->setText(QString("%1/%2").arg(page).arg(ui->stWidgetPage->count()));
}

void HNMPTableWidget::deleteItems()
{
    for(int i = 0; i < ui->stWidgetPage->count(); i++)
    {
        HNTableWidget* page = (HNTableWidget*)ui->stWidgetPage->widget(i);
        QMap<int, QStringList> ids;
        page->selectedRows(ids);
        QMapIterator<int, QStringList> itor(ids);
        while (itor.hasNext()) {
            itor.next();
            page->delItem(itor.key());
        }
    }
}

void HNMPTableWidget::setRecordNumPerPage(int num)
{
    m_numPerPage = num;
}

void HNMPTableWidget::setSelectionMode(QAbstractItemView::SelectionMode mode)
{
    selectionMode = mode;
}

void HNMPTableWidget::setResizeMode(QHeaderView::ResizeMode mode)
{
    resizeMode = mode;
}

void HNMPTableWidget::setResizeMode(int column, QHeaderView::ResizeMode mode)
{
    m_resizeMode.insert(column, mode);
}

void HNMPTableWidget::setAlternatingRowColors(bool alt)
{
    altColor = alt;
}

void HNMPTableWidget::setHeaderData(int i, Qt::Orientation, QString data)
{
    m_headerData.insert(i, data);
}

void HNMPTableWidget::setColumnWidth(int column, int width)
{
    m_columnWidth.insert(column, width);
}

void HNMPTableWidget::on_btnLeft_clicked()
{
    int index = ui->stWidgetPage->currentIndex();
    if(index > 0)
        index--;
    ui->stWidgetPage->setCurrentIndex(index);
    ui->lbPos->setText(QString("%1/%2").arg(index+1).arg(ui->stWidgetPage->count()));
}

void HNMPTableWidget::on_btnRight_clicked()
{
    int index = ui->stWidgetPage->currentIndex();
    if(index < ui->stWidgetPage->count()-1)
        index++;
    ui->stWidgetPage->setCurrentIndex(index);
    ui->lbPos->setText(QString("%1/%2").arg(index+1).arg(ui->stWidgetPage->count()));
}

void HNMPTableWidget::on_btnJump_clicked()
{
    int num = ui->leNum->text().toInt();
    if(num <= ui->stWidgetPage->count() && num > 0)
    {
        ui->stWidgetPage->setCurrentIndex(num-1);
        ui->lbPos->setText(QString("%1/%2").arg(num).arg(ui->stWidgetPage->count()));
    }
}

void HNMPTableWidget::on_btnLeftHead_clicked()
{
    ui->stWidgetPage->setCurrentIndex(0);
    ui->lbPos->setText(QString("%1/%2").arg(1).arg(ui->stWidgetPage->count()));
}

void HNMPTableWidget::on_btnRightHead_clicked()
{
    int index = ui->stWidgetPage->count()-1;
    ui->stWidgetPage->setCurrentIndex(index);
    ui->lbPos->setText(QString("%1/%2").arg(index+1).arg(ui->stWidgetPage->count()));
}
