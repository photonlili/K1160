#ifndef READXMLCONFIG_H
#define READXMLCONFIG_H

#include <QString>
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <QTextCodec>
#include "DataDef.h"

class ReadXmlConfig
{
public:
    ReadXmlConfig();
    ~ReadXmlConfig();
    QString getValue(const QString &key, const QString &type = "server");
    MachineSetting readxml();
    void writexml(MachineSetting *pmachinesetting = NULL);
private:
    QTextCodec  *m_ptc;
    QFile *m_pFile;
    QDomDocument *m_pDom;
};

#endif // READXMLCONFIG_H
