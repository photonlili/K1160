#include "hnfilesystem.h"
#include <QDir>
#include <QDirModel>
#include <QFileSystemModel>
#include <QFileSystemWatcher>

HNFileSystem::HNFileSystem(QObject *parent) :
    QObject(parent)
{

    m_client = HNClientInstance(parent);
    connect(m_client, SIGNAL(connected()), this, SLOT(slotSendLoginMsg()));
    connect(m_client, SIGNAL(signalConnectFail()), this, SIGNAL(openFail()));
    connect(m_client, SIGNAL(signalLogined()), this, SIGNAL(openSucc()));

    connect(m_client, SIGNAL(signalListFileOK()), this, SLOT(queryFilesResult()));
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
    m_client->setServPort(7079);
    m_client->SendConnectMessage();

    return false;
}

bool HNFileSystem::close()
{
    m_client->sendLogoutMessage();
    m_client->SendDisConnectFromHost();

    return true;
}

bool HNFileSystem::isOpen()
{
    return m_client->isLogined();
}

bool HNFileSystem::isQueryed()
{
    if(m_result.size() >0)
        return true;
    else
        return false;
}

bool HNFileSystem::query(QString path)
{
    QString prot; QString paths;
    parse(path, prot, paths);

    if(prot.contains("htp"))
    {
        if(!m_client->isLogined())
            return false;

        QString code = "";
        if(paths.isEmpty())
        {
            HNFileInfo f, f2;
            f.m_fileName = "Method";
            f.m_code = "001";
            f.m_filePath = "Method";
            f.m_prot = "htp://";
            f2.m_fileName = "Data";
            f2.m_code = "002";
            f2.m_filePath = "Data";
            f2.m_prot = "htp://";
            m_rootDir.clear();
            m_rootDir.push_back(f);            
            m_rootDir.push_back(f2);
            m_rootDir.m_code = "";
            m_rootDir.m_path = "";
            m_rootDir.m_prot = "htp://";
            m_rootDir.m_upcode = "";
            //OK
            m_result = m_rootDir;
            emit result(m_result);
            return true;
        }
        else if(paths.contains("Method"))
            code = "001";
        else if(paths.contains("Data"))
            code = "002";

        m_client->sendListFiles(code);
    }

    else if(prot.contains("local"))
    {
        QDir dir(paths);

        pline() << dir.exists();

        if(!dir.exists())
            return false;

        dir.setNameFilters(QDir::nameFiltersFromString(m_nameFileter));
        dir.setFilter(m_filter);
        dir.setSorting(m_sort);

        pline() << dir;

        QFileInfoList list = dir.entryInfoList();

        pline() << list.count();

        m_result.clear();
        QFileInfo qf;
        foreach (qf, list) {
            //pline() << qf.fileName() << qf.filePath() << qf.path() << qf.absolutePath() << qf.absoluteFilePath();
            HNFileInfo f;
            f.setFileInfo(qf);
            f.m_prot = "local://";
            m_result.push_back(f);
            m_result.m_code = "";
            m_result.m_path = dir.path();
            m_result.m_prot = "local://";
            m_result.m_upcode = "";
        }

        //OK
        emit result(m_result);
    }

    return true;
}


void HNFileSystem::queryFilesResult()
{
    QTCloudListFileResult r = m_client->GetListedFiles();
    _QTCloudListFileResult _r;

    m_result.clear();
    foreach (_r, r.m_file) {
        HNFileInfo f;
        f.m_fileName = _r.m_name;
        f.m_id = _r.m_id;
        f.m_size = _r.m_size;
        f.m_date = _r.m_date;
        f.m_prot = "htp://";
        if(r.m_code == "001")
            f.m_filePath = "Method";
        else if(r.m_code == "002")
            f.m_filePath = "Data";
        m_result.push_back(f);
        m_result.m_code = r.m_code;
        m_result.m_path = f.m_filePath;
        m_result.m_prot = "htp://";
        m_result.m_upcode = "";
    }

    if(r.m_code == "001")
        m_methodDir = m_result;
    else if(r.m_code == "002")
        m_dataDir = m_result;

    emit result(m_result);

}

void HNFileSystem::del(QString filePath)
{
    QString prot; QString files;
    parse(filePath, prot, files);

    if(prot.contains("local"))
    {
        system(QString("rm -f %1").arg(files).toAscii().constData());
        emit delSucc();
        return;
    }

    QString code;
    if(files.contains("Method"))
    {
        m_result = m_methodDir;
        code = "001";
    }
    else
    {
        m_result = m_dataDir;
        code = "002";
    }

    QString id = findID(files);

    pline() << code << id << files;
    //m_client->sendDelFile(code, id);
}

void HNFileSystem::copy(QString src, QString dst)
{
    QString prot; QString files;
    parse(src, prot, files);
    QString prot2; QString files2;
    parse(dst, prot2, files2);
    if(1)
    {
        QString srcFile, dstFile;
        QListIterator<HNFileInfo> itor3(m_methodDir.m_filelist);
        QListIterator<HNFileInfo> itor4(m_dataDir.m_filelist);
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
        QListIterator<HNFileInfo> itor3(m_rootDir.m_filelist);
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

HNFilesInfo &HNFileSystem::result()
{
    return m_result;
}

void HNFileSystem::parse(QString path, QString& protocolName, QString& files)
{
    if(path.contains("htp://"))
        protocolName = "htp://";
    else if(path.contains("local://"))
        protocolName = "local://";
    QStringList p0 = path.split("//");
    files = p0[1];
    //pline() << p0 << files;
}

QString HNFileSystem::findID(QString srcFile)
{
    QListIterator<HNFileInfo> itor(m_result.m_filelist);
    QString id;
    while(itor.hasNext())
    {
        HNFileInfo f = itor.next();
        if(f.m_fileName == srcFile)
        {
            id = f.m_id;
            break;
        }
    }
    return id;
}

void HNFileSystem::slotSendLoginMsg()
{
    m_client->sendLoginMessage();
}

HNFileSystem *HNFileSystemInstance(QObject *parent)
{
    static HNFileSystem* hnfs = new HNFileSystem(parent);
    return hnfs;
}
