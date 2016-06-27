#ifndef QSERIALPROTCOL_H
#define QSERIALPROTCOL_H

#include <QWidget>
#include <QByteArray>
#include <QThread>
#include "Serial/posix_qextserialport.h"
#include "DataDef.h"
class ReadThread : public QThread
{
    Q_OBJECT
public:
    explicit ReadThread(QObject *parent = 0);
    ~ReadThread();
  public:
    void run();
signals:
    void emitReadData(QByteArray pData);

public:
    QByteArray m_ReadData[5];
    //qint32  m_iIndex;
    Posix_QextSerialPort *m_pPosix;
};

class QSerialProtcol : public QWidget
{
    Q_OBJECT
public:
    explicit QSerialProtcol(QWidget *parent = 0);

signals:

public slots:
public:
    bool TransmitData(QByteArray &pCmd, QByteArray &pData);
private:
    ulong InitSerialPort();
    void InitReadThread();
    void SetCmdHead();
    void SetCmdSize(QByteArray pDataArry);
    void SetCmdCommand(QByteArray pDataArry);
    void SetCmdData(QByteArray pDataArry);
    void SetCmdCrc();
    void SetCmdTail();
public:
    ReadThread  *m_pReadThread;
    Posix_QextSerialPort *m_pPosix_QextSerialPort;
private:
    QByteArray  m_CommandSize;
    QByteArray  m_CommandCmd;
    QByteArray  m_CommandData;
    QByteArray  m_CommandVerifyCode;
    QByteArray m_ByteCmd;

};

QSerialProtcol * K1160SerialInst(QObject* parent = 0);

#endif // QSERIALPROTCOL_H
