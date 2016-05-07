#ifndef HNTREEMODEL_H
#define HNTREEMODEL_H

#include <QStandardItemModel>
#include "hnfilesystem.h"

class HNTreeModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit HNTreeModel(QObject *parent, HNFileSystem* fs);

    void query(int row, int column, const QModelIndex &parent = QModelIndex());
signals:

public slots:

private slots:
    void result(QList<HNFileInfo>);

private:
    HNFileSystem* m_fs;
    QModelIndex m_dirIndex;
    bool m_isQuerying;
};

#endif // HNTREEMODEL_H
