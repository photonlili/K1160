#include "hnmutipagefoundationwidget.h"
#include "ui_hnmutipagefoundationwidget.h"
#include "HNDefine.h"
#include "hntablewidget.h"
#include "hnmsgbox.h"
#include "hnprinter.h"
#include "hngraphicsview.h"
#include "hnpluginwatcher.h"
#include "hnprintinfodialog.h"


HNMutiPageFoundationWidget::HNMutiPageFoundationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNMutiPageFoundationWidget)
{
    ui->setupUi(this);
    r = HNReportInstance(this);
    connect(ui->btnLeft, SIGNAL(clicked()), ui->widgetSampleTable, SLOT(on_btnLeft_clicked()));
    connect(ui->btnRight, SIGNAL(clicked()), ui->widgetSampleTable, SLOT(on_btnRight_clicked()));
    pdfname = "K1160Report.pdf";
}

HNMutiPageFoundationWidget::~HNMutiPageFoundationWidget()
{
    delete ui;
}

void HNMutiPageFoundationWidget::initAll()
{

    //BK
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setGeometry(108,100,916,667);
    this->setStyleSheet("QWidget#HNMutiPageFoundationWidget{image:url(:/images/bk/bk_clean.png)}""HNMutiPageFoundationWidget{background-color:transparent;}");

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

    ui->widgetSampleTable->setDB(QString("%1/%2").arg(DB_DATA_PATH).arg(DB_DATA));
    ui->widgetSampleTable->setTable(TABLE_YANGPINDATA);
    ui->widgetSampleTable->query();

    ui->widgetSampleTable->setCurrentPage(1);
}

void HNMutiPageFoundationWidget::exportPdf()
{
    QVector<QStringList> lid;
    ui->widgetSampleTable->selectedItems(lid);
    HNTableWidget w11;
    w11.setDB(QString("%1/%2").arg(DB_DATA_PATH).arg(DB_DATA));
    w11.setTable(TABLE_YANGPINDATA);
    QString excp;
    for(int i = 0; i < lid.count() - 1; i++)
        excp += QString("id = %1 or ").arg(lid[i].at(ESampleId));
    excp += QString("id = %1").arg(lid.last().at(ESampleId));
    w11.query(excp);
    QAbstractItemModel* m_model = w11.model();
    m_model->setHeaderData(ESampleId, Qt::Horizontal, tr("No."));
    m_model->setHeaderData(ESampleMingcheng, Qt::Horizontal, tr("Name"));
    m_model->setHeaderData(ESampleBianhao, Qt::Horizontal, tr("Index"));
    m_model->setHeaderData(ESampleYangpinliang, Qt::Horizontal, tr("Dos"));
    m_model->setHeaderData(ESampleYangpindanwei, Qt::Horizontal, tr("ML"));
    m_model->setHeaderData(ESampleJieguo, Qt::Horizontal, tr("Result"));
    m_model->setHeaderData(ESampleJieguodanwei, Qt::Horizontal, tr("RML"));
    m_model->setHeaderData(ESampleCeshiren, Qt::Horizontal, tr("Tester"));
    m_model->setHeaderData(ESampleCeshishijian, Qt::Horizontal, tr("Time"));
    w11.horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    w11.setAlternatingRowColors(true);
    w11.resizeColumnsToContents();
    //w11.show();

    r->createSampleReport(header, footer, title, &w11);
    r->exportPdf(pdfname);
}

int HNMutiPageFoundationWidget::printInfoDlg()
{
    HNPrintInfoDialog dlg;
    dlg.initAll();
    int ret = dlg.exec();

    dlg.printInfo(title, header, footer);

    return ret;
}

void HNMutiPageFoundationWidget::on_btnPrint_clicked()
{
    QFile d(HNPluginWatcher::Instance()->printerFile());
    if(!d.exists())
    {
        HNMsgBox::warning(this, tr("Insert Printer, please!"));
        return;
    }

    //0000
    QVector<QStringList> lid;
    ui->widgetSampleTable->selectedItems(lid);
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

void HNMutiPageFoundationWidget::on_btnExport_clicked()
{
    QDir d(HNPluginWatcher::Instance()->upanMountPath());
    if(!d.exists())
    {
        HNMsgBox::warning(this, tr("Insert u disk, please!"));
        return;
    }

    QVector<QStringList> lid;
    ui->widgetSampleTable->selectedItems(lid);
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
    system(QString("cp -f %1 /mnt/usb_sda1/ & sync").arg(pdfname).toAscii().data());

    HNMsgBox::warning(this, tr("Export success"));
    ui->btnExport->setEnabled(true);

}

void HNMutiPageFoundationWidget::on_btnDelete_clicked()
{
    QVector<QStringList> lid;
    ui->widgetSampleTable->selectedItems(lid);
    if(lid.size() <= 0)
    {
        HNMsgBox::warning(this, tr("No selected"));
        return;
    }

    int ret = HNMsgBox::tips(this, tr("Delete this %1 items?").arg(lid.size()));
    if(HNMsgBox::Rejected == ret)
        return;

    ui->btnDelete->setEnabled(false);
    HNMsgBox box;
    box.information(tr("Deleting..."));


    int page = ui->widgetSampleTable->currentPage();
    ui->widgetSampleTable->deleteItems();
    ui->widgetSampleTable->query();
    int count = ui->widgetSampleTable->pageNum();
    if(page <= count)
        ui->widgetSampleTable->setCurrentPage(page);
    else
        ui->widgetSampleTable->setCurrentPage(count);

    HNMsgBox::warning(this, tr("Delete success"));
    ui->btnDelete->setEnabled(true);
}
