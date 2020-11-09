#ifndef CHATROOMMGR_H
#define CHATROOMMGR_H

#include <QObject>
#include "basesessionproxy.h"
#include "chatroom.h"
#include <QMap>

class ChatRoomMgr : public QObject
{
    Q_OBJECT
public:
    explicit ChatRoomMgr(QObject *parent = nullptr);
    void process(const QMap<QString,QString>& mp,const QByteArray& extradata,BaseSessionProxy* sp);
    bool addUserInRoom(const QString& roomId);
    bool removeUserInRoom(const QString& roomId);
    bool addRoom(const QString& roomId,const QString& roomTitle= "");
    void removeRoom(const QString& roomId);
    //void findRoom(const QString)
    bool isExistRoom(const QString& roomId);
    QStringList getRoomUsers(const QString& roomId);
    QStringList getConversation(const QString& roomId);//todo set update option
    QStringList insertChat(const QString& roomId,const QString& message);//todo set update option

private:
    QString generateRoomId(const QString& nickName);
    QMap<QString,QSharedPointer<ChatRoom>> mpRooms;
    ChatRoom CR;

};

#endif // CHATROOMMGR_H
