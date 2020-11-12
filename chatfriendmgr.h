#ifndef CHATFRIENDMGR_H
#define CHATFRIENDMGR_H

#include "basesessionproxy.h"
#include <QMap>

class UserInfoMgr;
class ChatUserDataMgr;

class ChatFriendMgr
{
public:
    explicit ChatFriendMgr(UserInfoMgr* uim);
    void process(const QMap<QString,QString>& mp,const QByteArray& extradata,BaseSessionProxy* sp);
    bool addFriend(const QString& nickname,const QString& friendname);
    bool removeFriend(const QString& nickname,const QString& friendname);
    bool isExistFriend(const QString& nickname,const QString& friendname);

    QStringList getFriendUsers();

private :
    UserInfoMgr* uim;
    ChatUserDataMgr* cudm;
    //QMap<
};

#endif // CHATFRIENDMGR_H
