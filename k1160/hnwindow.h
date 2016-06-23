#ifndef HNWINDOW_H
#define HNWINDOW_H

#include <QStackedWidget>

namespace Ui {
class HNWindow;
}

/**
 * @brief The HNWindow class
 * 窗口切换有绿屏 ，启动时的绿屏，解决。
 */
class HNWindow : public QStackedWidget
{
    Q_OBJECT

public:
    explicit HNWindow(QWidget *parent = 0);
    ~HNWindow();

private:
    Ui::HNWindow *ui;
};

#endif // HNWINDOW_H
