#include "qserialprotcol.h"


ReadThread::ReadThread(QObject *parent) :
    QThread(parent),
    m_pPosix(NULL)
{
    //m_pPosix = (Posix_QextSerialPort *)parent;m_pPosix_QextSerialPort
    m_pPosix = static_cast<Posix_QextSerialPort *>(parent);

}
ReadThread::~ReadThread()
{

}

void ReadThread::run()
{
    //qDebug("111111111111111111111111111111111111111111111.");
    while(true)
    {
        //sleep(1);
        usleep(10);
        if(true == m_pPosix->isReadable())
        {
            //int i = m_iIndex % 5;
            qint64 iRead = 0;
            m_ReadData[0].clear();
            iRead = m_pPosix->bytesAvailable();
            if(-1 != iRead)
            {
               // m_pPosix->readData(m_ReadData[i].data(), iRead);//m_ReadData.data(), 16);
              m_ReadData[0] = m_pPosix->readAll();
                //qDebug("ReadThread1.");
               if(!m_ReadData[0].isEmpty())
                {
                    //qDebug("ReadThread2.");
                    emit emitReadData(m_ReadData[0]);
                    //m_iIndex++;
                }
            }
        }
        //m_ReadData = m_pPosix->readAll();
    }
}

QSerialProtcol::QSerialProtcol(QWidget *parent) :
    QWidget(parent)
{
    InitSerialPort();
    InitReadThread();
}

//public
bool QSerialProtcol::TransmitData(QByteArray &pCmd, QByteArray &pData)
{
    m_ByteCmd.clear();
    if(pCmd.isEmpty())
        return false;

    SetCmdHead();
    SetCmdSize(pData);
    SetCmdCommand(pCmd);
    SetCmdData(pData);
    SetCmdCrc();
    SetCmdTail();

    //这个接口为上层的多线程操作做准备
    //但是上层没有多线程应用需求和结构
    if(m_pPosix_QextSerialPort->isWritable())
    {
       //m_pPosix_QextSerialPort->write(m_ByteCmd, m_ByteCmd.size());
        m_pPosix_QextSerialPort->write(m_ByteCmd, m_ByteCmd.size());
        return true;
    }
    return false;
}

//private
ulong QSerialProtcol::InitSerialPort()
{
    QString sPortName = "";
    PortSettings PortSetting;
#ifdef _MIPS_LINUX_ENV_
    sPortName = "/dev/ttyS1";
    PortSetting.BaudRate = BAUD115200;
    PortSetting.DataBits = DATA_8;
    PortSetting.Parity = PAR_NONE;
    PortSetting.StopBits = STOP_1;
    PortSetting.FlowControl = FLOW_OFF;
    PortSetting.Timeout_Millisec = 200;
#else
    sPortName = "/dev/ttyS0";
    PortSetting.BaudRate = BAUD9600;
    PortSetting.DataBits = DATA_8;
    PortSetting.Parity = PAR_NONE;
    PortSetting.StopBits = STOP_1;
    PortSetting.FlowControl = FLOW_OFF;
    PortSetting.Timeout_Millisec = 100;
#endif
    m_pPosix_QextSerialPort = new Posix_QextSerialPort(sPortName, PortSetting);

    if(NULL != m_pPosix_QextSerialPort) // Obj Create Successful!
      {
         if(m_pPosix_QextSerialPort->open(QIODevice::ReadWrite)) //Open Port dev.
         {
//             qDebug("111");
         }
         else
         {   //Open Port Dev Failed Of Err of DevOpening
             //export a Err Code.
           return m_pPosix_QextSerialPort->lastError();
         }
     }
     else
     {   //Obj Create Failed of Err of PortCreating
         //export a Err Code.
           return m_pPosix_QextSerialPort->lastError();
     }
     return E_NO_ERROR;
}

void QSerialProtcol::InitReadThread()
{
    m_pReadThread = new ReadThread(this->m_pPosix_QextSerialPort);
    m_pReadThread->start(QThread::NormalPriority);
    //connect(m_pReadThread, SIGNAL(emitReadData(QByteArray)),this, SLOT(AnalysisData(QByteArray)));
}

void QSerialProtcol::SetCmdHead()
{
    m_ByteCmd.append(0xAA);
    m_ByteCmd.append(0x55);
}


void QSerialProtcol::SetCmdSize(QByteArray pDataArry)
{
    m_CommandSize.clear();
    if(pDataArry.isEmpty())
     {
         m_CommandSize.append((char)0x00);
         m_CommandSize.append(0x0A);
     }
     else
     {
         qint32 iLen = pDataArry.size();
         iLen += 10;
         if(iLen > 255)
          {
             m_CommandSize.append(iLen >> 8);
             m_CommandSize.append(iLen & 0x00FF);
          }
          else
          {
             m_CommandSize.append((char)0x00);
             m_CommandSize.append(iLen);
          }
        }
    m_ByteCmd.append(m_CommandSize);
}

void QSerialProtcol::SetCmdCommand(QByteArray pDataArry)
{
    m_CommandCmd.clear();
    if(!pDataArry.isEmpty())
        m_ByteCmd.append(pDataArry);
    m_CommandCmd = pDataArry;
}

void QSerialProtcol::SetCmdData(QByteArray pDataArry)
{
    m_CommandData.clear();
    if(!pDataArry.isEmpty())
        m_ByteCmd.append(pDataArry);
    m_CommandData = pDataArry;
}

void QSerialProtcol::SetCmdCrc()
{
    uchar *p = NULL;
    int iSeek = 0;
    uint iSum = 0;
    m_CommandVerifyCode.clear();
    if(m_CommandData.isEmpty())
      {
         p = new uchar[4];
         memset(p, 0, 4);
      }
      else
      {
        int ilen = m_CommandData.size();
        p = new uchar[4 + ilen + 1];
        memset(p, 0, 4 + ilen+1);
      }

        for(int i = 0; i < m_CommandSize.size(); i++)
        {
            p[iSeek] = m_CommandSize.at(i);
            iSeek++;
        }

        for(int i = 0; i < m_CommandCmd.size(); i++)
        {
            p[iSeek] = m_CommandCmd.at(i);
            iSeek++;
        }

        if(!m_CommandData.isEmpty())
        {
            for(int i = 0; i < m_CommandData.size(); i++)
            {
                p[iSeek] = m_CommandData.at(i);
                iSeek++;
            }
        }

        for(int i = 0; i < iSeek; i++)
        {
            iSum += p[i];
        }

        if(iSum > 255)
        {
            int n;
            iSum = iSum & 0x00000000FFFF;
            n = iSum >> 8;
            iSum = iSum & 0x00FF;
            m_CommandVerifyCode.append(n);
            m_CommandVerifyCode.append(iSum);
        }
        else
        {
            m_CommandVerifyCode.append(char(0x00));
            m_CommandVerifyCode.append(iSum);
        }
        m_ByteCmd.append(m_CommandVerifyCode);
}

void QSerialProtcol::SetCmdTail()
{
    m_ByteCmd.append(0xCC);
    m_ByteCmd.append(0x33);
}

