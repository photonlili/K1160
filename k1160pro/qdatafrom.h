#ifndef QDATAFROM_H
#define QDATAFROM_H

#include <QWidget>
#include <QTextCodec>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QScrollBar>
#include "qdatabasequery.h"
#include "qmlabel.h"
#include "qlistgui.h"
#include "DataDef.h"
#include "qsqlquerycheckboxmodel.h"
#include "NetSource/simplenetwork.h"
#include "NetSource/NetDataCode.h"
#include "NetSource/NetControl.h"

class QSqlQueryModel;

namespace Ui {
class QDataFrom;
}

class QDataFrom : public QWidget
{
    Q_OBJECT


public:
    explicit QDataFrom(QWidget *parent = 0);
    ~QDataFrom();
    void StartSendFile();
    void Senddata();
    bool m_bDataDNOFalg;
    bool m_bSendFileFalg;
    int m_iIndex;
    int m_iLen;
    QSqlQueryModel *m_querymodel;
   // QSqlQueryCheckBoxModel *m_querymodel;
private slots:
    void on_pb_data_cloud_clicked();

    void on_pb_data_pgdn_clicked();

    void on_pb_data_pgup_clicked();

    void on_le_clean_jump_textEdited(const QString &arg1);

    void on_pb_data_export_clicked();

    void on_pb_data_delete_clicked();

    void on_tb_data_clicked(const QModelIndex &index);



    void on_le_clean_jump_textChanged(const QString &arg1);

    void on_pb_data_printer_clicked();
public slots:
    void Upfocus();
private:
    void InitOCX();

    void InitSings();

    int GetTotalCount(QString &strTable);

    int GetPageCount();

    void RecordQuery(int ilimit);

    void SetPageCount();

    void UpdateStatus();

    void SetSuyuan();

    void SendFileInfo();




private:


    QString m_stronelinedata;
    int m_icurrentpage;
    int m_itotalpage;
    int m_itotalcount;

    enum {m_epagecount = 20};

    QString     m_strexpress;
    QStringList linstname;
    QStringList linstvalues;
    QString     strtable;
    QDatabasequery *pdataquery;
    QSqlDatabase m_db;
    ListModel   *m_ItemModel;

    Ui::QDataFrom *ui;
    QTextCodec  *m_ptc;
    NetControl  *m_pNetControl;
    QStringList m_strFileList;
    int m_RemFileSize;
    QFile m_File;
};

#endif // QDATAFROM_H
