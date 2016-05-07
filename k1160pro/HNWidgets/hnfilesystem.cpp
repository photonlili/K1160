#include "hnfilesystem.h"
#include <QDir>
#include <QDirModel>
#include <QFileSystemModel>
#include <QFileSystemWatcher>

HNFileSystem::HNFileSystem(QObject *parent) :
    QObject(parent)
{
    m_client = new HNClient(parent);
    connect(m_client, SIGNAL(signalListDirOK()), this, SLOT(queryDirsResult()));
    connect(m_client, SIGNAL(signalListFileOK()), this, SLOT(queryFilesResult()));
    connect(m_client, SIGNAL(signalLogined()), this, SLOT(queryRootDirs()));
    //下载
    connect(m_client, SIGNAL(signalDownSucc()), this, SLOT(slotDownSuccess()));
    connect(m_client, SIGNAL(signalCancelDown()), this, SLOT(slotCancelDown()));
    //上传
    connect(m_client, SIGNAL(signalUploadSucc()), this, SLOT(slotUploadSuccess()));
    connect(m_client, SIGNAL(signalCancelUpload()), this, SLOT(slotUploadSuccess()));
}

HNFileSystem::~HNFileSystem()
{

}

bool HNFileSystem::open()
{
    m_stepStatus = EAUTO;
    m_client->setServPort(7079);
    m_client->SendConnectMessage();

    return true;
}

bool HNFileSystem::close()
{
    m_client->SendDisConnectFromHost();

    return true;
}

bool HNFileSystem::isOpen()
{
    return m_client->isLogined();
}

bool HNFileSystem::isQueryed()
{
    if(m_result.size()>0)
        return true;
    else
        return false;
}

void HNFileSystem::query(QString path)
{
    m_result.clear();

    QString prot; QString paths;
    parse(path, prot, paths);

    m_stepStatus = EQUERY;

    if(prot.contains("htp"))
    {
        QString code = "";
        if(paths.contains("Method"))
            code = "001";
        else
            code = "002";
        m_client->sendListFiles(code);
    }

    else if(prot.contains("local"))
    {
        QDir dir(paths);
        if(!dir.exists())
            return;

        dir.setNameFilters(QDir::nameFiltersFromString("*"));
        dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoSymLinks);

        QFileInfoList list = dir.entryInfoList();
        int file_count = list.count();
        if(file_count <= 0)
            return;

        QFileInfo qf;
        foreach (qf, list) {
            //pline() << qf.fileName() << qf.filePath() << qf.path() << qf.absolutePath() << qf.absoluteFilePath();
            HNFileInfo f;
            f.setFileInfo(qf);
            m_result.push_back(f);
        }

        //OK
        emit result(m_result);
        m_stepStatus = EAUTO;
    }

}


void HNFileSystem::queryResult()
{

}

void HNFileSystem::del(QString filePath)
{
    QString prot; QString files;
    parse(filePath, prot, files);
    QString srcFile, dstFile;

    QListIterator<HNFileInfo> itor3(m_rootDir);
    QString code;
    while(itor3.hasNext())
    {
        HNFileInfo f = itor3.next();
        if(f.m_filePath == files.at(0))
        {
            code = f.m_code;
            break;
        }
    }
    QListIterator<HNFileInfo> itor4(m_methodDir);
    QListIterator<HNFileInfo> itor5(m_dataDir);
    QString id;
    if(files.contains("Method"))
        while(itor4.hasNext())
        {
            HNFileInfo f = itor4.next();
            if(f.m_abslutFilePath == srcFile)
            {
                id = f.m_id;
                break;
            }
        }
    if(files.contains("Data"))
        while(itor5.hasNext())
        {
            HNFileInfo f = itor5.next();
            if(f.m_abslutFilePath == srcFile)
            {
                id = f.m_id;
                break;
            }
        }
    pline() << code << id << srcFile;
    //m_client->sendDelFile(code, id);
}

void HNFileSystem::copy(QString src, QString dst)
{
    QString prot; QString files;
    parse(src, prot, files);
    QString prot2; QString files2;
    parse(dst, prot2, files2);
    if("htp" == prot || "local" == prot2)
        m_stepStatus = true;
    if(m_stepStatus)
    {
        QString srcFile, dstFile;
        QListIterator<HNFileInfo> itor3(m_methodDir);
        QListIterator<HNFileInfo> itor4(m_dataDir);
        QString id;
        if(files.contains("Method"))
            while(itor3.hasNext())
            {
                HNFileInfo f = itor3.next();
                if(f.m_abslutFilePath == srcFile)
                {
                    id = f.m_id;
                    break;
                }
            }
        else if(files.contains("Data"))
            while(itor4.hasNext())
            {
                HNFileInfo f = itor4.next();
                if(f.m_abslutFilePath == srcFile)
                {
                    id = f.m_id;
                    break;
                }
            }
        pline() << srcFile << dstFile;
        //m_client->sendDownDevFiles(files.at(0), id, dstFile);
    }
    else
    {
        QString srcFile, dstFile;
        QListIterator<HNFileInfo> itor3(m_rootDir);
        QString code;
        while(itor3.hasNext())
        {
            HNFileInfo f = itor3.next();
            if(f.m_filePath == files.at(0))
            {
                code = f.m_code;
                break;
            }
        }
        QFileInfo f(srcFile);

        pline() << srcFile << dstFile << f.size();
        //m_client->sendUploadFile(code, files.at(0), files.at(1), f.size());
    }
}

void HNFileSystem::parse(QString path, QString& protocolName, QString& files)
{
    if(path.contains("htp://"))
        protocolName = "htp";
    else if(path.contains("local://"))
        protocolName = "local";
    QStringList p0 = path.split("//");
    files = p0[1];
    pline() << p0 << files;
}
