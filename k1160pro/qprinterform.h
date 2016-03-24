#ifndef QPRINTERFORM_H
#define QPRINTERFORM_H

#include <QWidget>
#include <QTextCodec>
#include "qmlabel.h"
#include "qdatabasequery.h"
#include "qdatafrom.h"


namespace Ui {
class QPrinterForm;
}

class QPrinterForm : public QWidget
{
    Q_OBJECT

public:
    explicit QPrinterForm(QWidget *parent = 0);
    ~QPrinterForm();
     QDatabasequery *pdataquery;
     QString     strtable;
     QStringList linstvalues;

private:
    void InitOCX();
    void InitSings();
    bool CreatPdf(QString &message, QString &message1, QString &message2);
    bool CreatPdfTatil(QString &message, QString &message1, QString &message2);
private slots:
    void psd();
    void bsd();
    void on_pushButton_back_clicked();

    void on_pushButton_start_clicked();

private:
    bool        m_bpsd;
    bool        m_bbsd;
    QMLabel     *m_pLbpsd;
    QMLabel     *m_pLbbsd;
    QDataFrom   *m_pDataFrom;
    Ui::QPrinterForm *ui;
    QTextCodec  *m_ptc;
    MachineSetting  m_machinesetting;
signals:
    void emitfocus();
};

#endif // QPRINTERFORM_H
