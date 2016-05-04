#ifndef HNMPTABLEWIDGET_H
#define HNMPTABLEWIDGET_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QHeaderView>

namespace Ui {
class HNMPTableWidget;
}

/**
 * @brief The HNMPTableWidget class
 * 关于视图规格的改变改变到上层
 * 这里的控件使用默认视图
 * 这里的控件只是Table-DB关系，没有Tree/List模型
 */
class HNMPTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HNMPTableWidget(QWidget *parent = 0);
    ~HNMPTableWidget();

    void setDB(QString db);
    void setTable(QString table);
    void setRecordNumPerPage(int num);
    void setSelectionMode(QAbstractItemView::SelectionMode mode = QAbstractItemView::MultiSelection);
    void setResizeMode(QHeaderView::ResizeMode mode = QHeaderView::ResizeToContents);
    void setResizeMode(int column, QHeaderView::ResizeMode mode = QHeaderView::ResizeToContents);
    void setAlternatingRowColors(bool alt = true);
    void setHeaderData(int i, Qt::Orientation, QString data);
    void setColumnWidth(int column, int width);
    void query(QString filter = "1=1");
    void selectedItems(QVector<QStringList> &lid);
    int pageNum();
    int currentPage();
    void setCurrentPage(int page);

public slots:
    void deleteItems();

private slots:
    void on_btnLeft_clicked();

    void on_btnRight_clicked();

    void on_btnJump_clicked();

    void on_btnLeftHead_clicked();

    void on_btnRightHead_clicked();

private:
    Ui::HNMPTableWidget *ui;
    QSqlDatabase m_db;
    QString m_name;
    QString m_table;
    int m_numPerPage ;
    QHash<int, QString> m_headerData;
    QHash<int, int> m_columnWidth;
    QHeaderView::ResizeMode resizeMode;
    QHash<int, QHeaderView::ResizeMode> m_resizeMode;
    QAbstractItemView::SelectionMode selectionMode;
    bool altColor;
};

#endif // HNMPTABLEWIDGET_H
