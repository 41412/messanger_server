#ifndef CHATSESSION_H
#define CHATSESSION_H
#include <QTcpSocket>
#include "chatpacketreceiver.h"

//QTcpsocket 상속
class ChatSession :  public QTcpSocket
{
public:
    ChatSession();
    virtual ~ChatSession();
    ChatPacketReceiver* getReceiver();

private:
    ChatPacketReceiver cpr;
};

#endif // CHATSESSION_H
