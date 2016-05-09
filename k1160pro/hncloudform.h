#ifndef HNCLOUDFORM_H
#define HNCLOUDFORM_H

#include <QWidget>
#include "hngui.h"

class HNCloudForm : public QWidget
{
    Q_OBJECT
public:
    explicit HNCloudForm(QWidget *parent = 0);


    bool open() {
        return treeWidget->open();
    }

    void queryRoot();


    void closehncfs() {
        treeWidget->closehncfs();
    }

    void InitOCX();

signals:

public slots:

private slots:
    void DeleteCloudItem();
    void slotSendQueryRoot();
    void UpDB();
    void DownDB();
    void status(int);
    void cancel();

private:
    HNPushButton* btnBack;
    HNPushButton* btnSync;
    HNPushButton* btnRefresh;
    HNPushButton* btnDelete;
    QLabel* labelTitle;
    HNTreeWidget* treeWidget;
    HNProgressDialog* m_pdlg;
    HNFileSystem* m_fs;
    QString m_srcPath;
    QString m_cloudfile;
    QString m_localfile;
};

#endif // HNCLOUDFORM_H
