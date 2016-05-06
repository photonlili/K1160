#ifndef HNTREEMODEL_H
#define HNTREEMODEL_H

#include <QStandardItemModel>

class HNTreeModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit HNTreeModel(QObject *parent = 0);

signals:

public slots:

};

#endif // HNTREEMODEL_H
