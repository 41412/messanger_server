#ifndef CHATROOMMGR_H
#define CHATROOMMGR_H

#include <QObject>
#include "basesessionproxy.h"
#include "chatroom.h"
#include <QSharedPointer>
#include <QMap>

class ChatRoomMgr : public QObject
{
    Q_OBJECT
public:
    explicit ChatRoomMgr(QObject *parent = nullptr);
    void process(const QMap<QString,QString>& mp,const QByteArray& extradata,BaseSessionProxy* sp);
    bool addUserInRoom(const QString& nickname,const QString& roomId);
    bool removeUserInRoom(const QString& roomId,const QString& nickname);
    bool addRoom(const QString& roomId,const QString& roomTitle= "");
    bool removeRoom(const QString& roomId);
    //void findRoom(const QString)
    bool isExistRoom(const QString& roomId);
    QStringList getRoomUsers(const QString& roomId);
    QStringList getConversation(const QString& roomId);//todo set update option
    int insertChat(const QString& roomId,const QString& nickname,const QString& message,const QString& date);//todo set update option

private:
    QString generateRoomId(const QString& nickName);
    QMap<QString,QSharedPointer<ChatRoom>> mpRooms;//key : roomId, value : ChatRoom
    ChatRoom CR;

};

#endif // CHATROOMMGR_H
