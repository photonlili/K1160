#ifndef HNMUTIPAGEFOUNDATIONWIDGET_H
#define HNMUTIPAGEFOUNDATIONWIDGET_H

#include <QWidget>
#include "hnreport.h"

namespace Ui {
class HNMutiPageFoundationWidget;
}

class HNMutiPageFoundationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HNMutiPageFoundationWidget(QWidget *parent = 0);
    ~HNMutiPageFoundationWidget();

public slots:
    void initAll();
    void exportPdf();
    int  printInfoDlg();

private slots:
    void on_btnPrint_clicked();

    void on_btnExport_clicked();

    void on_btnDelete_clicked();

private:
    Ui::HNMutiPageFoundationWidget *ui;
    HNReport* r;
    QString title, header, footer;
    QString pdfname;

};

#endif // HNMUTIPAGEFOUNDATIONWIDGET_H
