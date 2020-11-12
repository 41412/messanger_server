#include "chatfriendmgr.h"
#include "chatuserdatamgr.h"
#include "userinfomgr.h"
#include <QDebug>

ChatFriendMgr::ChatFriendMgr(UserInfoMgr* uim)
    : uim(uim)
{

}
bool ChatFriendMgr::addFriend(const QString& nickname,const QString& friendname)
{
    //key : nickname value : friendname
    if(uim->isExistName(friendname) == false)
    {
        qDebug() <<__FUNCTION__<<"already ";
        return false;
    }

    return cudm->addFriend(nickname,friendname);
}
bool ChatFriendMgr::removeFriend(const QString& nickname,const QString& friendname)
{
    return cudm->removeFriend(nickname,friendname);
}
//todo
bool ChatFriendMgr::isExistFriend(const QString& nickname,const QString& friendname)
{
    return false;
}

void ChatFriendMgr::process(const QMap<QString,QString>& mp,const QByteArray& extradata,BaseSessionProxy* sp)
{


}
