#ifndef HNFILESYSTEM_H
#define HNFILESYSTEM_H

#include "hnclient.h"
#include <QDir>
#include <QFileInfo>

class HNFileInfo
{
public:
    HNFileInfo(){}

    HNFileInfo setFileInfo(const QFileInfo &fileinfo)
    {
        m_isDir = fileinfo.isDir();
        m_path = fileinfo.path();
        m_filePath = fileinfo.filePath();
        m_abslutFilePath = fileinfo.absoluteFilePath();
        m_upcode;
        m_code;
        m_id;
        m_fileName = fileinfo.fileName();
        m_size = fileinfo.size();
        m_date = fileinfo.lastModified().toString("yyyy/MM/dd hh:mm");
        return *this;
    }

    HNFileInfo &operator=(const HNFileInfo &fileinfo)
    {
        m_isDir = fileinfo.m_isDir;
        m_path = fileinfo.m_path;
        m_filePath = fileinfo.m_filePath;
        m_abslutFilePath = fileinfo.m_abslutFilePath;
        m_upcode = fileinfo.m_upcode;
        m_code = fileinfo.m_code;
        m_id = fileinfo.m_id;
        m_fileName = fileinfo.m_fileName;
        m_size = fileinfo.m_size;
        m_date = fileinfo.m_date;
    }

    bool m_isDir;
    QString m_path;
    QString m_filePath;
    QString m_abslutFilePath;
    QString m_upcode;
    QString m_code;
    QString m_id;
    QString m_fileName;
    QString m_size;
    QString m_date;
};

/**
 * @brief The HNFileSystem class
 * 继承QObject不允许拷贝或者QSqlDatabase
 * 规格要求：QSqlDatabase
 * "local://"
 * "htp://"
 * "HNFS":"HNCFS"-"FS"
 */
class HNFileSystem : public QObject
{
    Q_OBJECT
public:
    HNFileSystem(QObject* parent = 0);
    ~HNFileSystem();

    bool open();
    bool close();
    bool isOpen();
    bool isQueryed();

    void query(QString path = "local:///");

    void create();//
    void del(QString filePath = "htp:///Method/");
    void copy(QString src = "local:///Method/system.db",
              QString dst = "htp:///Method");
    void cancel();
    int status();

    void parse(QString path, QString& protocolName, QString& files);

signals:
    void copySucc(QString dst);
    void copyFail(QString dst);
    void result(QList<HNFileInfo>);
private slots:
    void queryResult();
private:
    enum {
        EAUTO,
        EQUERY,
        EDOWN,
        EUPLOAD,
    };
    HNClient* m_client;
    QList<HNFileInfo> m_rootDir;
    QList<HNFileInfo> m_methodDir;
    QList<HNFileInfo> m_dataDir;
    QList<HNFileInfo> m_result;
    int m_stepStatus;
};

#endif // HNFILESYSTEM_H
