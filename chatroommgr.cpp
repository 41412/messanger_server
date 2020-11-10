#include "chatroommgr.h"
#include <QTime>
#include "chatdataprotocol.h"
#include <QDebug>

ChatRoomMgr::ChatRoomMgr(QObject *parent) : QObject(parent)
{   
#if defined(QT_DEBUG)
    mpRooms.insert("BOGUEN.2020.11.09.10.33.55", QSharedPointer<ChatRoom>(new ChatRoom("BOGUEN.2020.11.09.10.33.55","boguen")));
    mpRooms.last()->addUsers("mike,boguen,wooyoung");
#endif
}
bool ChatRoomMgr::addUserInRoom(const QString& nickname,const QString& roomId)
{


}
bool ChatRoomMgr::removeUserInRoom(const QString& roomId)
{

}

void ChatRoomMgr::process(const QMap<QString,QString>& mp,const QByteArray& extradata,BaseSessionProxy* sp)
{
    // 방 만들기 요청 프로토콜을 받음
    if(mp["id"] == "REQUEST_CREATE_CHATROOM")
    {
        //roomId 생성
        QString id = generateRoomId(mp["user"]);
        QByteArray ba = ChatDataProtocol::makeResCreateRoom(id);

        // insert room
        mpRooms.insert(id, QSharedPointer<ChatRoom>(new ChatRoom(id,mp["nickname"])));
        mpRooms.last()->addUsers(mp["members"]);

        // send room id to client
        sp->send(ba);
        // or
        // notify to all members in room that a room has been created
        // sp->send( user list, response for room creation );
    }

    //방에 속하는 유저들 목록 요청
    else if (mp["id"] == "req.userlist") {

        //방에 구성된 유저들에게 자기자신을 포함하여 방에 있는 모든 유저들의 리스트 전송



    }

    // 방 삭제 요청
    else if (mp["id"] == "req.remove.room") {

    }

    // 유저 추가
    else if (mp["id"] == "req.add.user") {

    }

    // 유저 삭제
    else if (mp["id"] == "req.remove.user") {

    }
    //대화 하기
    else if(mp["id"] == "REQUEST_SEND_CHAT")
    {
        //roomId를 받아옴
        QString roomId = mp["roomid"];
        QString timestamp = QDateTime::currentDateTimeUtc().toString("yyyy.MM.dd.hh:mm:ss.zzz");
        int index = -1;

        //방ID가 존재하지 않은 경우
        if(isExistRoom(roomId) == false)
        {
            qDebug() <<__FUNCTION__<<"nonexistent room";
        }
        else
        {
            //방ID가 존재하면 해당 방의 구성원들 정보를 가져옴
            QStringList roomUser = getRoomUsers(roomId);

            //구성원들에게 메시지 전송
            QByteArray message = mp["message"].toStdString().c_str();
            qDebug() <<__FUNCTION__<<"Server send"<< message;

            index = insertChat(roomId,mp["user"],message,timestamp);
            QByteArray body = ChatDataProtocol::makeResUpdateChat(roomId,mp["user"],timestamp,index,message);
            sp->send(roomUser,body);
        }
    }
}

bool ChatRoomMgr::addRoom(const QString& roomId,const QString& roomTitle)
{

}
bool ChatRoomMgr::removeRoom(const QString& roomId)
{
    //mpRooms에 지워야할 ID가 있는지 체크
    if(mpRooms.contains(roomId) == false)
    {
        qDebug() <<__FUNCTION__<<"nonexistent roomId";
        return false;
    }

    return true;
}

bool ChatRoomMgr::isExistRoom(const QString& roomId)
{
    //방ID가 존재하는지 체크
    for(QString id : mpRooms.keys())
    {
        if(roomId == id)
        {
            return true;
        }

    }
    return false;
}
QStringList ChatRoomMgr::getRoomUsers(const QString& roomId)
{
    QStringList roomUsers;

    if(mpRooms.contains(roomId))
    {
        roomUsers = mpRooms[roomId]->getRoomUserList();
    }


     return roomUsers;
}
QStringList ChatRoomMgr::getConversation(const QString& roomId)
{

}
int ChatRoomMgr::insertChat(const QString& roomId,const QString& nickname,const QString& message,const QString& date)
{
    if(mpRooms.contains(roomId))
    {
        return mpRooms[roomId]->storeChat(message,nickname,date);

    }
    else
    {
        return -1;
    }
}
QString ChatRoomMgr::generateRoomId(const QString& nickName )
{
    QString roomId = QDateTime::currentDateTimeUtc().toString("yyyy.MM.dd.hh:mm:ss.zzz") + nickName;

    return roomId;
}
