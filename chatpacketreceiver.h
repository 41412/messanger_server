#ifndef CHATPACKETRECEIVER_H
#define CHATPACKETRECEIVER_H

#include <QByteArray>
#include <QList>

class ChatPacketReceiver
{
public:
    ChatPacketReceiver();

    int process(const QByteArray& ba);
    QByteArray getPacket();
    int getPacketCount();

private:
    QList<QByteArray> packets;
    QByteArray buffer;
    qint32 remainSize;
};

#endif // CHATPACKETRECEIVER_H
