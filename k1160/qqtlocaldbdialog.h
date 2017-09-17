#ifndef QQTLOCALDBDIALOG_H
#define QQTLOCALDBDIALOG_H

#include "qqtgui-qt.h"
#include "qqtgui.h"

class QQTLocalDBDialog : public QQTDialog
{
    Q_OBJECT
public:
    explicit QQTLocalDBDialog(QWidget *parent = 0);

    void InitOCX();

    bool query(QString path = "local://db");
    void selectedItem(QString & path, QString& name);

signals:

public slots:
private slots:
    void currentRowChanged();
    void selected();

private:
    QQTTreeWidget* localWidget;
    QQTPushButton* btnSelect;
    QString m_path;
    QString m_name;
};

#endif // QQTLOCALDBDIALOG_H
