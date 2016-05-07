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

    QString prot; QStringList files;
    parse(path, prot, files);

    m_stepStatus = EQUERY;

    if("htp" == prot)
    {
        QString code = "";
        if(files[0] == "/Method")
            code = "001";
        else
            code = "002";
        m_client->sendListFiles(code);
    }

    else if("local" == prot)
    {
        QDir dir(path);
        if(!dir.exists())
            return;
        dir.setNameFilters(QDir::nameFiltersFromString("*.db"));
        dir.setFilter(QDir::Files | QDir::NoSymLinks);
        QFileInfoList list = dir.entryInfoList();
        int file_count = list.count();
        if(file_count <= 0)
            return;

        QFileInfo qf;
        foreach (qf, list) {
            HNFileInfo f;
            f.setFileInfo(qf);
            m_result.push_back(f);
        }

        //
        emit result(m_result);
        m_stepStatus = EAUTO;
    }

}

void HNFileSystem::del(QString filePath)
{
    QString prot; QStringList files;
    parse(filePath, prot, files);
    QString srcFile, dstFile;
    QStringListIterator itor(files);
    while(itor.hasNext())
        srcFile.append(itor.next());

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
    if(files.at(0) == "/Method")
        while(itor4.hasNext())
        {
            HNFileInfo f = itor4.next();
            if(f.m_abslutFilePath == srcFile)
            {
                id = f.m_id;
                break;
            }
        }
    else if(files.at(0) == "/Data")
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
    QString prot; QStringList files;
    parse(src, prot, files);
    QString prot2; QStringList files2;
    parse(dst, prot2, files2);
    if("htp" == prot || "local" == prot2)
        m_stepStatus = true;
    if(m_stepStatus)
    {
        QString srcFile, dstFile;
        QStringListIterator itor(files);
        while(itor.hasNext())
            srcFile.append(itor.next());
        QStringListIterator itor2(files2);
        while(itor2.hasNext())
            dstFile.append(itor2.next());
        QListIterator<HNFileInfo> itor3(m_methodDir);
        QListIterator<HNFileInfo> itor4(m_dataDir);
        QString id;
        if(files.at(0) == "/Method")
            while(itor3.hasNext())
            {
                HNFileInfo f = itor3.next();
                if(f.m_abslutFilePath == srcFile)
                {
                    id = f.m_id;
                    break;
                }
            }
        if(files.at(0) == "/Data")
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
        QStringListIterator itor(files);
        while(itor.hasNext())
            srcFile.append(itor.next());
        QStringListIterator itor2(files2);
        while(itor2.hasNext())
            dstFile.append(itor2.next());
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

void HNFileSystem::parse(QString path, QString protocolName, QStringList files)
{
    if(path.contains("htp://"))
        protocolName = "htp";
    else if(path.contains("local://"))
        protocolName = "local";
    QStringList p0 = path.split("/");
    pline() << p0;
    for(int i = 3; i < p0.size(); i++)
        files << "/" << p0[i];
}
