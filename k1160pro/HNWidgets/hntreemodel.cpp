#include "hntreemodel.h"
#include <QStandardItem>

HNTreeModel::HNTreeModel(QObject *parent, HNFileSystem* fs) :
    QStandardItemModel(parent), m_fs(fs)
{
    setColumnCount(FILE_MAX);
    connect(m_fs, SIGNAL(result(QList<HNFileInfo>)), this, SLOT(result0(QList<HNFileInfo>)));
}

void HNTreeModel::query(QString path)
{
    QString prot, file;
    m_dir = path;
    m_fs->query(path);
}


void HNTreeModel::result0(QList<HNFileInfo> fileList)
{
    QString prot, file;
    m_fs->parse(m_dir, prot, file);
    QList<QStandardItem*> itemList = findItems(file, Qt::MatchExactly, 1);
    pline() << "找到文件夹数目" << itemList.size() << prot << file;
    if(itemList.size() == 0)
    {
        removeRows(0, rowCount());
        setRowCount(0);
        int row = 0;
        QListIterator<HNFileInfo> itor(fileList);
        while(itor.hasNext())
        {
            HNFileInfo f = itor.next();
            insertRows(row, 1);
            setData(index(row, 0), f.m_fileName);
            setData(index(row, 1), f.m_filePath);
            row++;
        }
        submit();
        return;
    }

    QStandardItem *dir = item(itemList.at(0)->row(), 0);
    dir->removeRows(0, dir->rowCount());
    dir->setColumnCount(FILE_MAX);
    dir->setRowCount(0);

    int row = 0;
    QListIterator<HNFileInfo> itor(fileList);
    while(itor.hasNext())
    {
        HNFileInfo f = itor.next();
        pline() << f.m_fileName << f.m_filePath;
        dir->insertRows(row, 1);
        setData(index(row, 0, dir->index()), f.m_fileName);
        setData(index(row, 1, dir->index()), f.m_filePath);
        row++;
    }

    submit();
}
