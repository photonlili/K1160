#include "hnsampledatawidget.h"
#include "ui_hnsampledatawidget.h"
#include "HNDefine.h"
#include "hntablewidget.h"
#include "hnmsgbox.h"
#include "hnprinter.h"
#include "hngraphicsview.h"
#include "hnpluginwatcher.h"
#include "hnprintinfodialog.h"
#include "qsettingoriginsform.h"

enum ESampleMethod
{
    ESampleMethodId,
    ESampleMethodName,
    ESampledanbaixishu,
    ESamplepengsuan,
    ESamplexishishui,
    ESamplejian,
    ESamplezhengliu,
    ESamplezhengliudanwei,
    ESamplediding,
    ESamplejiajian,
    ESamplezhengqiliuliang,
    ESamplexiaohuaguan,
    ESamplejieshoubei,
    ESampleMethodMax,
};

#define TABLE_METHOD_K1160 "method"
#define DB_METHOD "method"
#define ESampleDataMethodID 9
#define ESampleDataEmptyV 10
#define ESampleDataDidingC 11
#define ESampleDataZhushi 12
#define ESampleDataMax 13


HNSampleDataWidget::HNSampleDataWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNSampleDataWidget)
{
    ui->setupUi(this);
    r = HNReportInstance(this);
    connect(ui->btnLeft, SIGNAL(clicked()), ui->widgetSampleTable, SLOT(on_btnLeft_clicked()));
    connect(ui->btnRight, SIGNAL(clicked()), ui->widgetSampleTable, SLOT(on_btnRight_clicked()));
    pdfname = "Report.pdf";
    ui->widgetSampleTable->setDB(QString("%1/%2").arg(DB_DATA_PATH).arg(DB_DATA));
    ui->widgetSampleTable->setTable(TABLE_YANGPINDATA);
}

HNSampleDataWidget::~HNSampleDataWidget()
{
    delete ui;
}

void HNSampleDataWidget::initAll()
{

    ptime(); //70ms
    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setGeometry(108,100,916,667);
    this->setStyleSheet("QWidget#HNSampleDataWidget{image:url(:/images/bk/bk_clean.png)}""HNSampleDataWidget{background-color:transparent;}");

    int btnH = 44;
    int btnW = 108;
    int btnX = 94;
    int btnXS = btnW + 35;
    int btnY = 578;

    //bt
    ui->btnLeft->setFlat(true);
    ui->btnLeft->setFocusPolicy(Qt::NoFocus);
    ui->btnLeft->setGeometry(btnX,btnY,108,44);
    ui->btnLeft->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_pgup_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_pgup_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_pgup_press.png);}");
    ui->btnLeft->setText("");
    ui->btnRight->setFlat(true);
    ui->btnRight->setFocusPolicy(Qt::NoFocus);
    ui->btnRight->setGeometry(btnX + btnXS * 1,btnY,108,44);
    ui->btnRight->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_pgdn_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_pgdn_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_pgdn_press.png);}");
    ui->btnRight->setText("");
    ui->btnPrint->setFlat(true);
    ui->btnPrint->setFocusPolicy(Qt::NoFocus);
    ui->btnPrint->setGeometry(btnX + btnXS * 2,btnY,108,44);
    ui->btnPrint->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_printer_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_printer_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_printer_press.png);}");
    ui->btnPrint->setText("");
    ui->btnDelete->setFlat(true);
    ui->btnDelete->setFocusPolicy(Qt::NoFocus);
    ui->btnDelete->setGeometry(btnX + btnXS * 3,btnY,108,44);
    ui->btnDelete->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_delete_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_delete_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_delete_press.png);}");
    ui->btnDelete->setText("");
    ui->btnExport->setFlat(true);
    ui->btnExport->setFocusPolicy(Qt::NoFocus);
    ui->btnExport->setGeometry(btnX + btnXS * 4,btnY,108,44);
    ui->btnExport->setStyleSheet("QPushButton{background-color:transparent;background-image: url(:/images/bt/bt_export_normal.png)}""QPushButton:hover{background-image: url(:/images/bt/bt_export_normal.png);}""QPushButton:pressed{background-image: url(:/images/bt/bt_export_press.png);}");
    ui->btnExport->setText("");
    ui->widgetSampleTable->setFocusPolicy(Qt::NoFocus);
    ui->widgetSampleTable->setGeometry(38, 41, 837, 540);

    ui->widgetSampleTable->setHeaderData(ESampleId, Qt::Horizontal, tr("No."));
    ui->widgetSampleTable->setHeaderData(ESampleMingcheng, Qt::Horizontal, tr("Name"));
    ui->widgetSampleTable->setHeaderData(ESampleBianhao, Qt::Horizontal, tr("Index"));
    ui->widgetSampleTable->setHeaderData(ESampleYangpinliang, Qt::Horizontal, tr("Dos"));
    ui->widgetSampleTable->setHeaderData(ESampleYangpindanwei, Qt::Horizontal, tr("ML"));
    ui->widgetSampleTable->setHeaderData(ESampleJieguo, Qt::Horizontal, tr("Result"));
    ui->widgetSampleTable->setHeaderData(ESampleJieguodanwei, Qt::Horizontal, tr("RML"));
    ui->widgetSampleTable->setHeaderData(ESampleCeshiren, Qt::Horizontal, tr("Tester"));
    ui->widgetSampleTable->setHeaderData(ESampleCeshishijian, Qt::Horizontal, tr("Time"));

    for(int i = ESampleDataMethodID; i < ESampleDataMax; i++)
        ui->widgetSampleTable->setColumnHidden(i);
    ptime();

    ui->widgetSampleTable->query();
    ui->widgetSampleTable->setCurrentPage(1);
}

void HNSampleDataWidget::refresh()
{
    HNMsgBox box;
    box.information(tr("Refreshing..."));
    ui->widgetSampleTable->query();
    ui->widgetSampleTable->setCurrentPage(1);
    box.accept();
}


void HNSampleDataWidget::exportPdf()
{
    QVector<QStringList> lid;
    ui->widgetSampleTable->selectedRows(ESampleId, lid);

    HNTableWidget* page = new HNTableWidget(this);
    page->setDB(QString("%1/%2").arg(DB_DATA_PATH).arg(DB_DATA));
    page->setTable(TABLE_YANGPINDATA);

    QString excp;
    for(int i = 0; i < lid.count() - 1; i++)
        excp += QString("id = '%1' or ").arg(lid[i].at(ESampleId));
    excp += QString("id = '%1'").arg(lid.last().at(ESampleId));
    page->query(excp);

    QAbstractItemModel* m_model = page->model();

    QSettings set;
    int value = set.value("ReportType", 0).toInt();
    if(0 == value)
    {

        m_model->setHeaderData(ESampleId, Qt::Horizontal, tr("No."));
        m_model->setHeaderData(ESampleMingcheng, Qt::Horizontal, tr("Name"));
        m_model->setHeaderData(ESampleBianhao, Qt::Horizontal, tr("Index"));
        m_model->setHeaderData(ESampleYangpinliang, Qt::Horizontal, tr("Dos"));
        m_model->setHeaderData(ESampleYangpindanwei, Qt::Horizontal, tr("ML"));
        m_model->setHeaderData(ESampleJieguo, Qt::Horizontal, tr("Result"));
        m_model->setHeaderData(ESampleJieguodanwei, Qt::Horizontal, tr("RML"));
        m_model->setHeaderData(ESampleCeshiren, Qt::Horizontal, tr("Tester"));
        m_model->setHeaderData(ESampleCeshishijian, Qt::Horizontal, tr("Time"));

        for(int i = ESampleDataMethodID; i < ESampleDataMax; i++)
            page->setColumnHidden(i, true);

        page->setFocusPolicy(Qt::NoFocus);
        QRect rect = r->clientRectF().toRect();
        page->setFixedSize(rect.width(), rect.height());
        page->setAlternatingRowColors(true);
        page->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);

        for(int i = 0; i < m_model->columnCount(); i++)
        {
            page->horizontalHeader()->setResizeMode(i, QHeaderView::ResizeToContents);
            page->setColumnWidth(i, 0);
        }

        r->createSampleReport(header, footer, title, page);
    }
    else
    {
        HNTableWidget* query = new HNTableWidget(this);
        query->setDB(QString("%1/%2").arg(DB_METHOD_PATH).arg(DB_METHOD));
        query->setTable(TABLE_METHOD_K1160);

        QList<QTableView*> table;
        for(int i = 0; i < m_model->rowCount(); i++)
        {
            QTableWidget* w = new QTableWidget(this);
            QRect rect = r->clientRectF().toRect();
            w->setFixedSize(rect.width(), rect.height());
            w->setAlternatingRowColors(false);
            w->horizontalHeader()->hide();
            w->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
            w->setColumnCount(8);
            w->setRowCount(10);
            w->setSpan(0, 1, 1, 7);
            w->setSpan(1, 1, 1, 2);
            w->setSpan(1, 4, 1, 2);
            w->setSpan(2, 1, 1, 2);
            w->setSpan(2, 4, 1, 4);

            for(int i = 3; i <=6; i++ )
            {
                w->setSpan(i, 0, 1, 2);
                w->setSpan(i, 2, 1, 2);
                w->setSpan(i, 4, 1, 2);
                w->setSpan(i, 6, 1, 2);
            }

            w->setSpan(8, 1, 1, 7);
            w->setSpan(9, 1, 1, 7);

            QAbstractItemModel* model = w->model();

            QStringList dl;
            for(int j = 0; j < ESampleDataMax; j++)
                dl << page->model()->data(page->model()->index(i, j)).toString();
            pline() << dl;

            query->query(QString("id = %1").arg(dl[ESampleDataMethodID]));

            QStringList ml;
            for(int j = 0; j < ESampleMethodMax; j++)
                ml << query->model()->data(query->model()->index(0, j)).toString();
            pline() << ml;

            model->setData(model->index(0, 0), "序号");
            model->setData(model->index(0, 1), dl[ESampleId]);

            model->setData(model->index(1, 0), "样品名称");
            model->setData(model->index(1,1), dl[ESampleMingcheng]);
            model->setData(model->index(1,3), "样品量");
            model->setData(model->index(1,4), dl[ESampleYangpinliang]);
            model->setData(model->index(1,6), "样品编号");
            model->setData(model->index(1, 7), dl[ESampleBianhao]);

            model->setData(model->index(2,0), "测试类型");
            model->setData(model->index(2,1), "样品");
            model->setData(model->index(2,3), "结果");
            model->setData(model->index(2,4), dl[ESampleJieguo]);

            model->setData(model->index(3,0), "空白体积");
            model->setData(model->index(3,2), dl[ESampleDataEmptyV]);
            model->setData(model->index(3,4), "滴定酸浓度");
            model->setData(model->index(3,6), dl[ESampleDataDidingC]);

            model->setData(model->index(4,0), "蛋白系数");
            model->setData(model->index(4,2), ml[ESampledanbaixishu]);
            model->setData(model->index(4,4), "蒸汽流量");
            model->setData(model->index(4,6), ml[ESamplezhengqiliuliang]);

            QString xiaohuaguan;
            if(ml[ESamplexiaohuaguan].toInt()==0)
                xiaohuaguan = "关";
            else if(ml[ESamplexiaohuaguan].toInt()==1)
                xiaohuaguan = "开";

            QString jieshoubei;
            if(ml[ESamplejieshoubei].toInt()==0)
                jieshoubei = "关";
            else if(ml[ESamplejieshoubei].toInt()==1)
                jieshoubei = "开";

            model->setData(model->index(5,0), "消化管排废");
            model->setData(model->index(5,2), xiaohuaguan);
            model->setData(model->index(5,4), "接收杯排废");
            model->setData(model->index(5,6), jieshoubei);

            QString didingfangshi;
            if(ml[ESamplediding].toInt()==0)
                didingfangshi = "边蒸馏边滴定";
            else if(ml[ESamplediding].toInt()==1)
                didingfangshi = "先蒸馏后滴定";
            QString jiajianfangshi;
            if(ml[ESamplejiajian].toInt()==0)
                jiajianfangshi = "先加碱后蒸馏";
            else if(ml[ESamplejiajian].toInt()==1)
                jiajianfangshi = "先蒸馏后加碱";

            model->setData(model->index(6,0), "滴定方式");
            model->setData(model->index(6,2), didingfangshi);
            model->setData(model->index(6,4), "加碱方式");
            model->setData(model->index(6,6), jiajianfangshi);

            model->setData(model->index(7,0), "碱");
            model->setData(model->index(7,1), ml[ESamplejian]);
            model->setData(model->index(7,2), "蒸馏");
            model->setData(model->index(7,3), ml[ESamplezhengliu]);
            model->setData(model->index(7,4), "硼酸");
            model->setData(model->index(7,5), ml[ESamplepengsuan]);
            model->setData(model->index(7,6), "稀释水");
            model->setData(model->index(7,7), ml[ESamplexishishui]);

            model->setData(model->index(8,0), "备注");
            model->setData(model->index(8,1), dl[ESampleDataZhushi]);
            model->setData(model->index(9,0), "事件");

            table.push_back(w);
        }

        query->setDB();
        delete query;

        r->CreateComplexReport(header, footer, title, table);

        //for 删除widget
        QListIterator<QTableView*> itor(table);
        while(itor.hasNext())
        {
            QTableView* view = itor.next();
            delete view;
        }
        table.clear();
    }

    page->setDB();
    delete page;

    r->exportPdf(pdfname);
}

int HNSampleDataWidget::printInfoDlg()
{
    HNPrintInfoDialog dlg;
    dlg.initAll();
    int ret = dlg.exec();

    dlg.printInfo(title, header, footer);

    return ret;
}

void HNSampleDataWidget::on_btnPrint_clicked()
{
    QFile d(HNPluginWatcher::Instance()->printerFile());
    if(!d.exists())
    {
        HNMsgBox::warning(this, tr("Insert Printer, please!"));
        return;
    }

    //0000
    QVector<QStringList> lid;
    ui->widgetSampleTable->selectedRows(ESampleId, lid);
    if(lid.size() <= 0)
    {
        HNMsgBox::warning(this, tr("No selected"));
        return;
    }

    int ret = printInfoDlg();
    if(QDialog::Rejected == ret)
        return;

    ui->btnPrint->setEnabled(false);
    HNMsgBox box;
    box.information(tr("Printing..."));

    exportPdf();
    r->print();

    HNMsgBox::warning(this, tr("Print success"));
    ui->btnPrint->setEnabled(true);
}


void HNSampleDataWidget::on_btnExport_clicked()
{

#ifdef __MIPS_LINUX__
    QDir d(HNPluginWatcher::Instance()->upanMountPath());
    if(!d.exists())
    {
        HNMsgBox::warning(this, tr("Insert u disk, please!"));
        return;
    }
#endif

    QVector<QStringList> lid;
    ui->widgetSampleTable->selectedRows(ESampleId, lid);
    if(lid.size() <= 0)
    {
        HNMsgBox::warning(this, tr("No selected"));
        return;
    }

    int ret = printInfoDlg();
    if(QDialog::Rejected == ret)
        return;

    ui->btnExport->setEnabled(false);
    HNMsgBox box;
    box.information(tr("Exporting..."));

    exportPdf();

    system(QString("rm -f  /mnt/usb_sda1/%1").arg(pdfname).toAscii().data());
    HNSleep(250);

#if 0
    //导出 pc删除 导出 - 在一部分U盘上会拷贝失败
    system(QString("rm -f  /mnt/usb_sda1/%1").arg(pdfname).toAscii().data());
    system(QString("cp -f %1 /mnt/usb_sda1/ & sync").arg(pdfname).toAscii().data());
#elif 0
    //第一遍导出失败
    system(QString("cp -f %1 /mnt/usb_sda1/ & sync").arg(pdfname).toAscii().data());
#elif 1
    //第二遍导出成功，解决有问题的U盘
    system(QString("cp -f %1 /mnt/usb_sda1/").arg(pdfname).toAscii().data());
    HNSleep(250);
    system(QString("cp -f %1 /mnt/usb_sda1/ & sync").arg(pdfname).toAscii().data());
    HNSleep(250);
#endif

    HNMsgBox::warning(this, tr("Export success"));
    ui->btnExport->setEnabled(true);

}

void HNSampleDataWidget::on_btnDelete_clicked()
{
    QVector<QStringList> lid;
    ui->widgetSampleTable->selectedRows(ESampleId, lid);
    if(lid.size() <= 0)
    {
        HNMsgBox::warning(this, tr("No selected"));
        return;
    }

    int ret = HNMsgBox::question(this, tr("Delete this %1 items?").arg(lid.size()));
    if(HNMsgBox::Rejected == ret)
        return;

    ui->btnDelete->setEnabled(false);
    HNMsgBox box;
    box.information(tr("Deleting..."));


    int page = ui->widgetSampleTable->currentPage();
    int count = ui->widgetSampleTable->pageNum();
    //pline() << page << count;

    ui->widgetSampleTable->removeSelectedRows(ESampleId);
    ui->widgetSampleTable->query();
    count = ui->widgetSampleTable->pageNum();
    if(page <= count)
        ui->widgetSampleTable->setCurrentPage(page);
    else
        ui->widgetSampleTable->setCurrentPage(count);
    //pline() << page << count;

    HNMsgBox::warning(this, tr("Delete success"));
    ui->btnDelete->setEnabled(true);

    HNCreateSysEvent("删除样品数据");

}
