#ifndef HNMUTIPAGEWIDGET_H
#define HNMUTIPAGEWIDGET_H

#include <QWidget>
#include <QSqlRelationalTableModel>

namespace Ui {
class HNMutiPageWidget;
}

class HNMutiPageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HNMutiPageWidget(QWidget *parent = 0);
    ~HNMutiPageWidget();

    void setDB(QString db);
    void setTable(QString table);
    void setRecordNumPerPage(int num);
    void query();
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
    Ui::HNMutiPageWidget *ui;
    QSqlDatabase m_db;
    QString m_name;
    QString m_table;
    int m_numPerPage ;
};

#endif // HNMUTIPAGEWIDGET_H
