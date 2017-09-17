#ifndef QQTUSERINFOWIDGET_H
#define QQTUSERINFOWIDGET_H

#include "qqttableview.h"
#include "qqttablemodel.h"
#include <QDataWidgetMapper>

#include <QItemDelegate>

class QQTUserInfoViewTextDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    QQTUserInfoViewTextDelegate(QObject *parent = 0): QItemDelegate(parent) { }

    // QItemDelegate interface
protected:
    void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;
};

namespace Ui {
class QQTUserInfoView;
}

namespace Ui {
class QQTUserInfoWidget;
}

class QQTUserInfoWidget : public QQTTableView
{
    Q_OBJECT

public:
    explicit QQTUserInfoWidget(QWidget *parent = 0);
    ~QQTUserInfoWidget();

    void refresh();
    void selectUser(int id = 0);
    void selectUser(QString userName);
    QString currentUser();
    QString currentUserAuthority();
    QString currentUserPassword();
    void setUserName(QString newName);
    inline QDataWidgetMapper* mapper() { return m_mapper; }
    inline QQTTableModel* model() { return m_model; }
    inline void addMap(QWidget* w, int section) { m_mapper->addMapping(w, section); }
    inline void addMap(QWidget* w, int section, const QByteArray &propertyName) { m_mapper->addMapping(w, section, propertyName); }
    void initLanguage();

public slots:
    void newUser(QString name, QString pwd, QString auth, QString comt);
    void delUser();
    void updateMap();
    void saveMap();

private slots:
    void currentItemChanged(QModelIndex,QModelIndex);
private:
    Ui::QQTUserInfoWidget *ui;

    QQTTableModel* m_model;
    QDataWidgetMapper* m_mapper;

    QQTUserInfoViewTextDelegate* m_dg;
};

#endif // QQTUSERINFOWIDGET_H
