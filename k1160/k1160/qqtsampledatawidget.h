#ifndef QQTSAMPLEDATAWIDGET_H
#define QQTSAMPLEDATAWIDGET_H

#include <QWidget>
#include "qqtreport.h"

namespace Ui {
class QQTSampleDataWidget;
}

class QQTSampleDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QQTSampleDataWidget(QWidget *parent = 0);
    ~QQTSampleDataWidget();

public slots:
    void initAll();
    void refresh();

private slots:
    void on_btnPrint_clicked();

    void on_btnExport_clicked();

    void on_btnDelete_clicked();

private:
    void exportPdf();
    int  printInfoDlg();
    Ui::QQTSampleDataWidget *ui;
    QQTReport* r;
    QString title, header, footer;
    QString pdfname;

};

#endif // QQTSAMPLEDATAWIDGET_H
