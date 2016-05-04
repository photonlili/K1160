#ifndef HNTABLEWIDGET_H
#define HNTABLEWIDGET_H

#include "hntableview.h"
#include "hntablemodel.h"

namespace Ui {
class HNTableWidget;
}

class HNTableWidget : public HNTableView
{
    Q_OBJECT

public:
    explicit HNTableWidget(QWidget *parent = 0);
    ~HNTableWidget();

    void setDB(QString db);
    void setTable(QString table);
    void query(QString excp = "");
    void delItem(int row);

    void selectedRows(QMap<int, QStringList> &ids);

private:
    Ui::HNTableWidget *ui;
    HNTableModel* m_model;
    QSqlDatabase m_db;
};

#endif // HNTABLEWIDGET_H
