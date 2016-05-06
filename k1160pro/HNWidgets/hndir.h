#ifndef HNFILESYSTEM_H
#define HNFILESYSTEM_H

#include <QObject>

class QHash;
class QDir;
class QFile;
class QFileInfo;
class HNClient;

/**
 * @brief The HNFileSystem class
 * 支持QDir协议 "FS"
 * 支持HTP协议  "HNFS"
 */
class HNFileSystem : public QObject
{
    Q_OBJECT
public:
    explicit HNFileSystem(QObject *parent = 0);

    bool open();
    bool close();
    bool isOpen();

    void setRootPath(const QString& name);
    void setUserName(const QString& name);
    void setPassword(const QString& password);
    void setHostName(const QString& host);
    void setPort(int p);
    void rootPath();
    QString userName();
    QString passWord();
    QString port();
    QString hostName();
    HNFileSystem &operator=(const HNFileSystem &other);

    void query(QString path, QString filter);

signals:

public slots:
    void queryResult(QString path);
private:
    QString m_uri;
    QString m_rootPath;
    HNClient* m_client;
    QDir m_dir;
    QString m_fsName;
    QString m_fsType;

private:
    //static HNFileSystem addFileSystem(QString type, QString name);
    //name, type
    //static QHash<QString, QString> fsTable;
};

#endif // HNFILESYSTEM_H
