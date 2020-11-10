#include "chatroom.h"
#include <QDebug>

ChatRoom::ChatRoom()
{

}

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

int ChatRoom::storeChat(const QString& chat,const QString& nickname,const QString& date)
{

    return cc.addChat(date,nickname,chat);

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
            //break;//->?
        }
    }

    return false;
}
//todo **
bool ChatRoom::addUser(const QString& nickname)
{


    return false;
}
bool ChatRoom::addUsers(const QString& nickname, const QString& delimiter)
{
    QStringList nicknameList = nickname.split(delimiter);

    for(auto n: nicknameList) {
        //기존에 있는 닉네임 체크
        if(roomUserNames.contains(n) == true)
        {
            qDebug() << "User already exists.";
        }
        else
        {
            roomUserNames.push_back(n);
        }
    }

    return true;
}

