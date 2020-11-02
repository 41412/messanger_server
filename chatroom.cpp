#include "chatroom.h"

chatRoom::chatRoom(QString roomId,QString title,QString admin)
{//변수 초기화

    this->roomId = roomId;
    this->title = title;
    this->admin = admin;

}



void chatRoom::setRoomID(QString nickName)
{
    roomId = QTime::currentTime().toString() + nickName;
}

QString chatRoom::getRoomId()
{
    return roomId;
}



