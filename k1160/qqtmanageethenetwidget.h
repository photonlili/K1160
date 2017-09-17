#ifndef QQTMANAGEETHENETWIDGET_H
#define QQTMANAGEETHENETWIDGET_H

#include <QWidget>

namespace Ui {
class QQTManageEthenetWidget;
}

class QQTManageEthenetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QQTManageEthenetWidget(QWidget *parent = 0);
    ~QQTManageEthenetWidget();

    void initAll();

private slots:
    void netChanged();
    void wifiConnected();
    void wifiDisConnected();

    void on_btn_saveip_clicked();

    void on_chk_dhcp_stateChanged(int arg1);

private:
    Ui::QQTManageEthenetWidget *ui;
};

#endif // QQTMANAGEETHENETWIDGET_H
