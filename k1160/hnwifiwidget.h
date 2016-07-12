#ifndef HNWIFIWIDGET_H
#define HNWIFIWIDGET_H

#include "hnstandarditemmodel.h"
#include "hngui-qt.h"
#include "hngui.h"
#include "hnpassworddialog.h"
#include <QItemDelegate>
#include <QStylePainter>
#include "HNDefine.h"

class HNWIFIIDTextDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    HNWIFIIDTextDelegate(QObject *parent = 0): QItemDelegate(parent), parent(parent) { }

private:
    QObject* parent;

    // QItemDelegate interface
protected:
    void drawCheck(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, Qt::CheckState state) const;

    // QItemDelegate interface
protected:
    void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;
};

namespace Ui {
class HNWIFIWidget;
}

class HNWIFIWidget : public HNTableView
{
    Q_OBJECT

public:
    explicit HNWIFIWidget(QWidget *parent = 0);
    ~HNWIFIWidget();

private slots:
    void clickWIFI();
    void wifiRefreshed();
protected:
    TWifi currentWifi();
    bool setCurrentWifi(QString bssid_mac, QString password = "");
private:
    HNEthManager* m_pManager;
    HNWIFIIDTextDelegate* dg;

private:
    Ui::HNWIFIWidget *ui;
    HNStandardItemModel* m_model;
    HNPasswordDialog* m_pass;
};

#endif // HNWIFIWIDGET_H
