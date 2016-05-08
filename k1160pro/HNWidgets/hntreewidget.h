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

    void open()
    { m_fs->open(); }
    void close()
    { m_fs->close(); }

    //从查询结果中过滤出rootpath里面的内容进行保存；
    void setRootPath();
    //过滤，排序
    inline void setNameFilter(QString filter)
    { m_model->setNameFilter(filter); }
    inline void setFilter(QDir::Filters filter = QDir::Dirs | QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot)
    { m_model->setFilter(filter); }
    inline void setSorting(QDir::SortFlags sort = QDir::DirsFirst | QDir::Name | QDir::Reversed)
    { m_model->setSorting(sort); }

    void query(QString path = "local://.");

private slots:
    void currentRowChanged();

private:
    Ui::HNTreeWidget *ui;
    HNTreeModel* m_model;
    HNFileSystem* m_fs;
    QString m_prot;
};

#endif // HNTREEWIDGET_H
