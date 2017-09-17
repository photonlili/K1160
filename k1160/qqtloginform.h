#ifndef QQTLOGINFORM_H
#define QQTLOGINFORM_H

#include <QWidget>

namespace Ui {
class QQTLoginForm;
}

class QQTLoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit QQTLoginForm(QWidget *parent = 0);
    ~QQTLoginForm();

private slots:
    void on_btnLogin_clicked();

private:
    Ui::QQTLoginForm *ui;
};

#endif // QQTLOGINFORM_H
