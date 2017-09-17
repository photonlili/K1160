#ifndef QQTCLOUDFORM_H
#define QQTCLOUDFORM_H

#include <QWidget>
#include "qqtgui.h"
#include "qqtlocaldbdialog.h"
#include "qqtprogressdialog.h"

class QQTCloudForm : public QWidget
{
    Q_OBJECT
public:
    explicit QQTCloudForm(QWidget *parent = 0);


    bool open() {
        return treeWidget->open();
    }


    void closeQQTcfs() {
        treeWidget->closeQQTcfs();
    }

    void queryRoot();

signals:
    void downSucc();

public slots:

private slots:
    void DeleteCloudItem();
    void UpDB();
    void DownDB();
    void status(int);
    void cancel();

private:
    void InitOCX();
    QQTPushButton* btnBack;
    QQTPushButton* btnSync;
    QQTPushButton* btnRefresh;
    QQTPushButton* btnDelete;
    QLabel* labelTitle;
    QQTTreeWidget* treeWidget;
    QQTLocalDBDialog* localDlg;
    QQTProgressDialog* m_pdlg;
    QQTFileSystem* m_fs;
    QString m_srcPath;
    QString m_cloudfile;
    QString m_localfile;

};

#endif // QQTCLOUDFORM_H
