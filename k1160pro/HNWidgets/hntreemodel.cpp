#include "hntreemodel.h"
#include <QStandardItem>

HNTreeModel::HNTreeModel(QObject *parent, HNFileSystem* fs) :
    QStandardItemModel(parent), m_fs(fs)
{
    connect(m_fs, SIGNAL(result()),
            this, SLOT(result()));
}

bool HNTreeModel::query(QString path)
{
    m_path = path;
    bool ret = m_fs->query(path);

    return ret;
}

bool HNTreeModel::removeRow(int arow, const QModelIndex &aparent)
{
    //fs
    QString prot, name;
    m_fs->parse(m_path, prot, name);


    QString path = data(index(aparent.row(), 1)).toString();
    QString file = data(index(arow, 0, aparent)).toString();

    QString sPath = QString("%1%2/%3").arg(prot).arg(path).arg(file);
    m_fs->del(sPath);
    return QStandardItemModel::removeRow(arow, aparent);
}

void HNTreeModel::result()
{


    QString prot, file;
    m_fs->parse(m_path, prot, file);

    pline() << m_path << prot << file;


    if(prot.contains("local"))
        return;

    HNFilesInfo files = m_fs->record();

    //在云查询中，QT存在bug，大数据下，每一组信号和槽都被调用。
    if(prot != files.m_prot)
        return;

    QList<QStandardItem*> itemList = findItems(file, Qt::MatchExactly, 1);
    pline() << "找到文件夹数目" << itemList.size() << prot << file;

    if(itemList.size() == 0)
    {
        removeRows(0, rowCount());
        setColumnCount(FILE_MAX);
        setRowCount(0);
        int row = 0;
        QListIterator<HNFileInfo> itor(files.m_filelist);
        while(itor.hasNext())
        {
            HNFileInfo f = itor.next();
            insertRows(row, 1);
            setData(index(row, 0), f.m_fileName);
            setData(index(row, 1), f.m_filePath);
            row++;
        }
    }
    else
    {
        QStandardItem *dir = item(itemList.at(0)->row(), 0);
        dir->removeRows(0, dir->rowCount());
        dir->setColumnCount(FILE_MAX);
        dir->setRowCount(0);

        int row = 0;
        QListIterator<HNFileInfo> itor(files.m_filelist);
        while(itor.hasNext())
        {
            HNFileInfo f = itor.next();
            pline() << f.m_fileName << f.m_filePath;
            dir->insertRows(row, 1);
            setData(index(row, 0, dir->index()), f.m_fileName);
            setData(index(row, 1, dir->index()), f.m_filePath);
            row++;
        }
    }


    submit();
}
