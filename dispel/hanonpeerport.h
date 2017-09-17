#ifndef QQTPEERPORT_H
#define QQTPEERPORT_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "hanonpeermessage.h"
#include "HanonDefine.h"

//屏通过这个类和单片机进行通信
class HanonPeerPort : public QSerialPort
{
    Q_OBJECT
public:
    explicit HanonPeerPort(QObject *parent = 0);
    ~HanonPeerPort();

    void setHeatParam(quint8 stage, quint8 vessel, quint16 ramp, quint16 press, quint16 hold);
    void sendMsgConnectToC51();
    void sendMsgHeatPress(quint8 stage, quint8 vessel, quint16 press);
    void sendMsgHeatStandard(quint8 stage, quint8 vessel, quint16 tempture, quint16 hold);
    void sendMsgHeatRAMP(quint8 stage, quint8 vessel, quint16 ramp, quint16 press, quint16 tempture, quint16 hold);
    void sendMsgHeatExtract(quint8 stage, quint16 tempture, quint16 hold);
    void sendMsgPause();
    void sendMsgStop();

signals:
    void sigRecvMsg(QByteArray msg);
    void sigPeerException(int eCode);

private slots:
    void sendConnectToC51();
    void sendHeatPress();
    void sendHeatStandard();
    void sendHeatRAMP();
    void sendHeatExtract();
    void sendPause();
    void sendStop();

private slots:
    void readyReadData();
    void updateProgress(qint64);
    void dispatchRecvedMessage(QByteArray &blockOnNet);
    void SendSerialMessage();
private:
    void recvCmdAck(const QByteArray &l);
    void recvCmdNAck(const QByteArray &l);

    enum{
        Heat_Standart,
        Heat_Press,
        Heat_Ramp,
        Heat_Extract,
    };

    QTimer* timer;
    quint16 m_cmdCount;
    quint16 m_msgType;
    quint16 m_heatType;
    QQTHeatRAMPStruct m_heat;
};

HanonPeerPort *HanonPeerPortInstance(QObject* parent = 0);

#endif // QQTPEERPORT_H
