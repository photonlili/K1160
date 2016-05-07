#include "hntreemodel.h"
#include <QStandardItem>

HNTreeModel::HNTreeModel(QObject *parent, HNFileSystem* fs) :
    QStandardItemModel(parent), m_fs(fs), m_isQuerying(false)
{
    connect(m_fs, SIGNAL(result(QList<HNFileInfo>)), this, SLOT(retult(QList<HNFileInfo>)));
}

void HNTreeModel::query(int row, int column, const QModelIndex &parent)
{
    if(m_isQuerying)
        return;
    m_isQuerying = true;
    m_dirIndex = index(row, column, parent);
    QString path = data(m_dirIndex).toString();
    m_fs->query(path);
}

void HNTreeModel::result(QList<HNFileInfo> fileList)
{
    QStandardItem* dir = itemFromIndex(m_dirIndex);
    if(NULL == dir)
        return;

    dir->removeRows(0, dir->rowCount());
    dir->removeColumns(0, dir->columnCount());
    dir->setColumnCount(1);
    dir->setRowCount(0);

    int row = 0;
    QListIterator<HNFileInfo> itor(fileList);
    while(itor.hasNext())
    {
        HNFileInfo f = itor.next();
        dir->insertRows(row, 1);
        setData(index(row, 0, dir->index()), f.m_fileName);
        row++;
    }

    submit();

    m_isQuerying = false;
}
