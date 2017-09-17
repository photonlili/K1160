#ifndef QQTSUYUANFORM_H
#define QQTSUYUANFORM_H

#include <QWidget>
#include "qqtmptablewidget.h"

class QQTSuyuanForm : public QWidget
{
    Q_OBJECT
public:
    explicit QQTSuyuanForm(QWidget *parent = 0);

signals:

public slots:

private:
    QQTMPTableWidget* m_table;
};

#endif // QQTSUYUANFORM_H
