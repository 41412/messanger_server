#include "chatroommgr.h"
#include <QTime>
#include "chatdataprotocol.h"
#include <QSharedPointer>

ChatRoomMgr::ChatRoomMgr(QObject *parent) : QObject(parent)
{

}
bool ChatRoomMgr::addUserInRoom(const QString& roomId)
{

}
bool ChatRoomMgr::removeUserInRoom(const QString& roomId)
{

}

void ChatRoomMgr::process(const QMap<QString,QString>& mp,const QByteArray& extradata,BaseSessionProxy* sp)
{
    // 방 만들기 요청 프로토콜을 받음
    if(mp["id"] == "req.create.room")
    {
        //roomId 생성
        QString id = generateRoomId(mp["nickname"]);
        QByteArray ba = ChatDataProtocol::makeResCreateRoom(id);

        // inser room
        mpRooms.insert(id, QSharedPointer<ChatRoom>(new ChatRoom(id, "", mp["nickname"])));

        // send room id to client
        //sp->send(ba);
        // or
        // notify to all members in room that a room has been created
        // sp->send( user list, response for room creation );
    }

    //방에 속하는 유저들 목록 요청
    else if (mp["id"] == "req.userlist") {

        //클라이언트가


    }

    // 방삭재 요청
    else if (mp["id"] == "req.remove.room") {

    }

    // 유저 추가
    else if (mp["id"] == "req.add.user") {

    }

    // 유저 삭제
    else if (mp["id"] == "req.remove.user") {

    }
    //...
}

bool ChatRoomMgr::addRoom(const QString& roomId,const QString& roomTitle)
{

}
void ChatRoomMgr::removeRoom(const QString& roomId)
{

}

bool ChatRoomMgr::isExistRoom(const QString& roomId)
{

}
QStringList ChatRoomMgr::getRoomUsers(const QString& roomId)
{

}
QStringList ChatRoomMgr::getConversation(const QString& roomId)
{

}
QStringList ChatRoomMgr::insertChat(const QString& roomId,const QString& message)
{

}
QString ChatRoomMgr::generateRoomId(const QString& nickName )
{
    QString roomId = QTime::currentTime().toString() + nickName;

    return roomId;
}
