#ifndef QQTMAINFORM_H
#define QQTMAINFORM_H

#include <QWidget>

namespace Ui {
class QQTMainForm;
}

class QQTMainForm : public QWidget
{
    Q_OBJECT

public:
    explicit QQTMainForm(QWidget *parent = 0);
    ~QQTMainForm();

    void init();

public slots:
    void setUser();
    void setTheme();
    void setHead();
    void setLanguage();
    void wifiConnected();
    void wifiDisConnected();
    void wifiConnecting();

private:
    Ui::QQTMainForm *ui;

    // QObject interface
public:
    bool eventFilter(QObject *, QEvent *);
};

#endif // QQTMAINFORM_H
