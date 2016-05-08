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



    void closehncfs() {
        treeWidget->closehncfs();
    }

    void InitOCX();

signals:

public slots:

private slots:
    void slotSendQueryRoot();

private:
    HNPushButton* btnBack;
    HNPushButton* btnSync;
    HNPushButton* btnRefresh;
    HNPushButton* btnDelete;
    QLabel* labelTitle;
    HNTreeWidget* treeWidget;
};

#endif // HNCLOUDFORM_H
