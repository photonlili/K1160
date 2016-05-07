#include "hntreemodel.h"
#include <QStandardItem>

HNTreeModel::HNTreeModel(QObject *parent, HNFileSystem* fs) :
    QStandardItemModel(parent), m_fs(fs), m_isQuerying(false)
{
    connect(m_fs, SIGNAL(result(QList<HNFileInfo>)), this, SLOT(result(QList<HNFileInfo>)));
}

void HNTreeModel::query(QString path)
{
    if(m_isQuerying)
        return;
    m_isQuerying = true;
    m_dir = path;
    m_fs->query(path);
}


void HNTreeModel::result(QList<HNFileInfo> fileList)
{
    QList<QStandardItem*> itemList = findItems(m_dir, Qt::MatchExactly, 0);
    pline() << itemList.size();
    QStandardItem* dir = itemList.at(0);
    if(NULL == dir)
    {
        removeRows(0, rowCount());
        removeColumns(0, columnCount());
        setColumnCount(FILE_MAX);
        setRowCount(0);
        int row = 0;
        QListIterator<HNFileInfo> itor(fileList);
        while(itor.hasNext())
        {
            HNFileInfo f = itor.next();
            insertRows(row, 1);
            setData(index(row, 0), f.m_fileName);
            row++;
        }
        submit();
        m_isQuerying = false;
        return;
    }

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
