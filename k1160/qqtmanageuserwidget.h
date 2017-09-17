#ifndef QQTMANAGEUSERWIDGET_H
#define QQTMANAGEUSERWIDGET_H

#include <QWidget>

namespace Ui {
class QQTManageUserWidget;
}

class QQTManageUserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QQTManageUserWidget(QWidget *parent = 0);
    ~QQTManageUserWidget();

private slots:
    void on_btnNewUser_clicked();

    void on_btnDelUser_clicked();

private:
    Ui::QQTManageUserWidget *ui;
};

#endif // QQTMANAGEUSERWIDGET_H
