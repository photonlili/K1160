#ifndef HNWINDOW_H
#define HNWINDOW_H

#include <QStackedWidget>

namespace Ui {
class HNWindow;
}

/**
 * @brief The HNWindow class
 * 窗口切换有绿屏 ，启动时的绿屏，解决。
 * 窗口跳转不再经过信号和槽，而是通过这个注册的主窗的函数
 */
class HNWindow : public QStackedWidget
{
    Q_OBJECT

public:
    explicit HNWindow(QWidget *parent = 0);
    ~HNWindow();

    void setLoginForm();
    void setMainForm();
    void setSelfCheckForm();

private:
    Ui::HNWindow *ui;
};

#endif // HNWINDOW_H
