#include "chatroom.h"

ChatRoom::ChatRoom(QString roomId,QString admin)
{//변수 초기화

    this->roomId = roomId;

    this->admin = admin;

}



void ChatRoom::setRoomID(QString nickName)
{
    roomId = QTime::currentTime().toString() + nickName;
}

QString ChatRoom::getRoomId()
{
    return roomId;
}

void ChatRoom::storeChat(const QString& chat,const QString& nickname,const QString& date)
{
    cc.addChat(date,nickname,chat);

}
QStringList ChatRoom::getRoomUserList()
{
    //nickname과 일치하는 경우
    //해당 닉네임이 속해 있는 방ID 반환

    return roomUserNames;
}
bool ChatRoom::isUserRoom(const QString& nickName)
{
    qint32 i=0;

    for(i=0;i<roomUserNames.size();i++)
    {
        if(nickName == roomUserNames[i])
        {
            return true;
            break;
        }
    }

    return false;
}

