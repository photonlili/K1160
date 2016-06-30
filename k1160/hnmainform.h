#ifndef HNMAINFORM_H
#define HNMAINFORM_H

#include <QWidget>

namespace Ui {
class HNMainForm;
}

class HNMainForm : public QWidget
{
    Q_OBJECT

public:
    explicit HNMainForm(QWidget *parent = 0);
    ~HNMainForm();

    void init();

public slots:
    void setUser();
    void setTheme();
    void setPic();
    void setLanguage();
    void wifiConnected();
    void wifiDisConnected();
    void wifiConnecting();

private:
    Ui::HNMainForm *ui;

    // QObject interface
public:
    bool eventFilter(QObject *, QEvent *);
};

#endif // HNMAINFORM_H
