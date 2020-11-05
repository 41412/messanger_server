#include "chatfriendmgr.h"
#include "userinfomgr.h"

ChatFriendMgr::ChatFriendMgr(UserInfoMgr* uim)
    : uim(uim)
{

}
void ChatFriendMgr::process(const QMap<QString,QString>& mp,const QByteArray& extradata,BaseSessionProxy* sp)
{

}
