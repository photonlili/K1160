#ifndef HNTREEMODEL_H
#define HNTREEMODEL_H

#include <QStandardItemModel>
#include "hnfilesystem.h"

class HNTreeModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit HNTreeModel(QObject *parent, HNFileSystem* fs);

    //从查询结果中过滤出rootpath里面的内容进行保存；
    void setRootPath();
    void query(QString path);
signals:

public slots:

private slots:
    void result(QList<HNFileInfo>);

private:

    HNFileSystem* m_fs;
    QString m_dir;
    bool m_isQuerying;
};

#endif // HNTREEMODEL_H
