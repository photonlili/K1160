#include "hnmutipagewidget.h"
#include "ui_hnmutipagewidget.h"
#include "HNDefine.h"
#include "hngui.h"

HNMutiPageWidget::HNMutiPageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNMutiPageWidget)
{
    ui->setupUi(this);

    m_db = newDatabaseConn();
    m_numPerPage = 14;

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

HNMutiPageWidget::~HNMutiPageWidget()
{
    delete ui;
}

void HNMutiPageWidget::setDB(QString db)
{
    m_name = db;
    setDatabaseName(m_db, m_name);
}

void HNMutiPageWidget::setTable(QString table)
{
    m_table = table;
}

void HNMutiPageWidget::query()
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
        page->query(QString("1=1 limit %1 offset %2").arg(m_numPerPage).arg(i*m_numPerPage));
        page->setSelectionMode(HNTableWidget::MultiSelection);
        page->setAlternatingRowColors(true);
        page->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
        page->resizeColumnsToContents();;
        ui->stWidgetPage->addWidget(page);
    }
}

void HNMutiPageWidget::selectedItems(QVector<QStringList> &lid)
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

int HNMutiPageWidget::pageNum()
{
    return ui->stWidgetPage->count();
}

int HNMutiPageWidget::currentPage()
{
    return ui->stWidgetPage->currentIndex();
}

void HNMutiPageWidget::setCurrentPage(int page)
{
    if(page < 1 || page > ui->stWidgetPage->count())
        return;
    ui->stWidgetPage->setCurrentIndex(page-1);
    ui->lbPos->setText(QString("%1/%2").arg(page).arg(ui->stWidgetPage->count()));
}

void HNMutiPageWidget::deleteItems()
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

void HNMutiPageWidget::setRecordNumPerPage(int num)
{
    m_numPerPage = num;
}

void HNMutiPageWidget::on_btnLeft_clicked()
{
    int index = ui->stWidgetPage->currentIndex();
    if(index > 0)
        index--;
    ui->stWidgetPage->setCurrentIndex(index);
    ui->lbPos->setText(QString("%1/%2").arg(index+1).arg(ui->stWidgetPage->count()));
}

void HNMutiPageWidget::on_btnRight_clicked()
{
    int index = ui->stWidgetPage->currentIndex();
    if(index < ui->stWidgetPage->count()-1)
        index++;
    ui->stWidgetPage->setCurrentIndex(index);
    ui->lbPos->setText(QString("%1/%2").arg(index+1).arg(ui->stWidgetPage->count()));
}

void HNMutiPageWidget::on_btnJump_clicked()
{
    int num = ui->leNum->text().toInt();
    if(num <= ui->stWidgetPage->count() && num > 0)
    {
        ui->stWidgetPage->setCurrentIndex(num-1);
        ui->lbPos->setText(QString("%1/%2").arg(num).arg(ui->stWidgetPage->count()));
    }
}

void HNMutiPageWidget::on_btnLeftHead_clicked()
{
    ui->stWidgetPage->setCurrentIndex(0);
    ui->lbPos->setText(QString("%1/%2").arg(1).arg(ui->stWidgetPage->count()));
}

void HNMutiPageWidget::on_btnRightHead_clicked()
{
    int index = ui->stWidgetPage->count()-1;
    ui->stWidgetPage->setCurrentIndex(index);
    ui->lbPos->setText(QString("%1/%2").arg(index+1).arg(ui->stWidgetPage->count()));
}
