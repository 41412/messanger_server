#include "chatuserdata.h"

ChatUserData::ChatUserData(const QString& nickname)
    : nickname(nickname)
{

}


QString ChatUserData::getNickName()
{
    return nickname;
}

QStringList ChatUserData::getFriendList()
{
    if (friendlist.empty()) {
        return QStringList();
    }
    return friendlist.values();
}
bool ChatUserData::addFriend(const QString& friendname)
{
    if(friendlist.contains(friendname) == true)
    {
        return false;
    }

    friendlist.insert(friendname);

    return true;
}
bool ChatUserData::removeFriend(const QString& friendname)
{
    return friendlist.remove(friendname);
}
int  ChatUserData::getCountFriend()
{
    return friendlist.count();
}
