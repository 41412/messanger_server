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

    void setNickName(const QString& nickname){
        name = nickname;
    }
    const QString& getNickName() {
        return name;
    }

private:
    ChatPacketReceiver cpr;
    QString name;
};

#endif // CHATSESSION_H
