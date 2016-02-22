#ifndef QSETTINGNETFORM_H
#define QSETTINGNETFORM_H

#include <QWidget>
#include <QTextCodec>
#include "qmlabel.h"
#include "wifi/qwifiwidget.h"
#include "wifi/qwifimanager.h"

namespace Ui {
class QSettingNetForm;
}

class QSettingNetForm : public QWidget
{
    Q_OBJECT

public:
    explicit QSettingNetForm(QWidget *parent = 0);
    ~QSettingNetForm();
private slots:
    void on_pb_zhixing_clicked();
private slots:
    void dhcp();
    void wifipwd();
    void NetChanged();
    void wifiPassDone(QString password);
private:
    void InitOCX();
    void InitSings();
private:
    QWIFIWidget *m_pwifi;
    HNEthManager *m_pwifiManager;
    QMLabel *m_pDHCP;
    QMLabel *m_pDHCPText;
    QString m_strpwd;
    bool    m_bDHCP;
    Ui::QSettingNetForm *ui;
    QTextCodec  *m_ptc;
};

#endif // QSETTINGNETFORM_H
