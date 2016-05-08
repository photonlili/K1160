#ifndef HNCLOUDFORM_H
#define HNCLOUDFORM_H

#include <QWidget>
#include "hngui.h"

class HNCloudForm : public QWidget
{
    Q_OBJECT
public:
    explicit HNCloudForm(QWidget *parent = 0);


    void open() {
        treeWidget->open();
    }
    void close() {
        treeWidget->closehncfs();
    }

    void InitOCX();

signals:

public slots:

private:
    HNPushButton* btnBack;
    HNPushButton* btnSync;
    HNPushButton* btnRefresh;
    HNPushButton* btnDelete;
    QLabel* labelTitle;
    HNTreeWidget* treeWidget;
};

#endif // HNCLOUDFORM_H
