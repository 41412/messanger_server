#ifndef CHATFRIENDMGR_H
#define CHATFRIENDMGR_H

#include "basesessionproxy.h"
#include "userinfomgr.h"

class ChatFriendMgr
{
public:
    explicit ChatFriendMgr(UserInfoMgr* uim);
    void process(const QMap<QString,QString>& mp,const QByteArray& extradata,BaseSessionProxy* sp);

private :
    UserInfoMgr* uim;
};

#endif // CHATFRIENDMGR_H
