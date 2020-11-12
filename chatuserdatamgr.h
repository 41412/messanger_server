#ifndef CHATUSERDATAMGR_H
#define CHATUSERDATAMGR_H

#include "basesessionproxy.h"
#include "chatuserdata.h"
#include <QSharedPointer>
#include <QMap>

class ChatRoomMgr;
class ChatFriendMgr;

class ChatUserDataMgr
{

public:
    explicit ChatUserDataMgr( ChatRoomMgr* rm, ChatFriendMgr* fm);
    void process(const QMap<QString,QString>& mp,const QByteArray& extradata,BaseSessionProxy* sp);
    bool addFriend(const QString& fromUser,const QString& friendName);
    bool removeFriend(const QString& fromUser,const QString& friendName);

    bool addUser(const QString& nickname);
    QStringList getFriendList(const QString& nickname);


private:
    QMap<QString,QSharedPointer<ChatUserData>>mpUsers;
    ChatRoomMgr* rm;
    ChatFriendMgr* fm;
};

#endif // CHATUSERDATAMGR_H
