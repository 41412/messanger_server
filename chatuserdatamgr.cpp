#include "chatuserdatamgr.h"
#include "chatdataprotocol.h"
#include "chatuserdata.h"
#include "chatroommgr.h"
#include "chatfriendmgr.h"
#include <QDebug>

ChatUserDataMgr::ChatUserDataMgr(ChatRoomMgr* rm, ChatFriendMgr* fm)
    :rm(rm),fm(fm)
{

}


bool ChatUserDataMgr::addFriend(const QString& fromUser,const QString& friendName)
{
    return mpUsers[fromUser]->addFriend(friendName);
}
bool ChatUserDataMgr::removeFriend(const QString& fromUser,const QString& friendName)
{
    return mpUsers[fromUser]->removeFriend(friendName);
}

bool ChatUserDataMgr::addUser(const QString& nickname)
{
    mpUsers.insert(nickname,QSharedPointer<ChatUserData>(new ChatUserData(nickname)));

    return true;
}
QStringList ChatUserDataMgr::getFriendList(const QString& nickname)
{

    return mpUsers[nickname]->getFriendList();
}

void ChatUserDataMgr::process(const QMap<QString,QString>& mp,const QByteArray& extradata,BaseSessionProxy* sp)
{
    if (!mp.contains("id")) { return; }


    if(mp["target"] == "room")
    {
        rm->process(mp, extradata,sp);
    }

    else
    {
        if(mp["id"] == "REQUEST_USERDATA")
        {
            sp->send(ChatDataProtocol::makeSendStart());
        }
        else if(mp["id"] == "READY_TO_RECEIVE")
        {
            QMap<QString, QString> smp;

            // friend list
            QString userName= sp->getUserName(); //

            sp->send(ChatDataProtocol::makeSendFriendList(mpUsers[userName]->getFriendList()));

            // room
            smp["id"] = "SEND_CHATROOMLIST";
            smp["user"] = userName;
            rm->process(smp, QByteArray(), sp);

            // end
            sp->send(ChatDataProtocol::makeSendEnd());
        }
    }



}
