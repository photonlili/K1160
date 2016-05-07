#ifndef HNTREEWIDGET_H
#define HNTREEWIDGET_H

#include "hntreeview.h"
#include "hntreemodel.h"
#include "hnfilesystem.h"

namespace Ui {
class HNTreeWidget;
}

/**
 * @brief The HNTreeWidget class
 * 仅仅用于文件系统显示和功能
 */
class HNTreeWidget : public QTreeView
{
    Q_OBJECT

public:
    explicit HNTreeWidget(QWidget *parent = 0);
    ~HNTreeWidget();

    void query(QString path = "local://.");

private:
    Ui::HNTreeWidget *ui;
    HNTreeModel* m_model;
    HNFileSystem* m_fs;
};

#endif // HNTREEWIDGET_H
