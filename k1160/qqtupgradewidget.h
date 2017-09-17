#ifndef QQTUPGRADEWIDGET_H
#define QQTUPGRADEWIDGET_H

#include <QWidget>
#include "qqtclient.h"
#include "qqtgui-qt.h"
#include "qqtcloudprotocol.h"

class QBackupLocalThread : public QThread
{
public:
    explicit QBackupLocalThread(QObject *parent = 0) : QThread(parent){}

    // QThread interface
protected:
    void run();
};

class QUpgradeThread : public QThread
{
public:
    explicit QUpgradeThread(QObject *parent = 0) : QThread(parent){}
    // QThread interface
protected:
    void run();
};

namespace Ui {
class QQTUpgradeWidget;
}

class QQTUpgradeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QQTUpgradeWidget(QWidget *parent = 0);
    ~QQTUpgradeWidget();

    void initAll();

signals:
    void sigCancelUpgrade();

private slots:
    void setText(QString text);
    void setValue(int value);
    void download();
    void logined();
    void versionR();
    void downOK();
    void restart();

    void on_btnDown_clicked();

    void on_btnCancel_clicked();

    void on_btnCheck_clicked();

private:
    Ui::QQTUpgradeWidget *ui;
    QQTClient* m_cli;
    QQTCloudProtocol* m_protocol;
    QTimer* timer;
    QBackupLocalThread* m_backupT;
    QUpgradeThread* m_upgradeT;
    QString m_newSoftwareID;
};

#endif // QQTUPGRADEWIDGET_H
