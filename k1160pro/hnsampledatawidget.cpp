#include "hnsampledatawidget.h"
#include "ui_hnsampledatawidget.h"
#include "HNDefine.h"
#include "hntablewidget.h"
#include "hnmsgbox.h"
#include "hnprinter.h"
#include "hngraphicsview.h"
#include "hnpluginwatcher.h"
#include "hnprintinfodialog.h"


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
    HNTableWidget* page = ui->widgetSampleTable->selectedRows(ESampleId);

    r->createSampleReport(header, footer, title, page);
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
    system(QString("cp -f %1 /mnt/usb_sda1/ & sync").arg(pdfname).toAscii().data());
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
}
