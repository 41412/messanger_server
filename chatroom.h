#ifndef CHATROOM_H
#define CHATROOM_H

#include <QObject>
#include <QTime>
#include "chatconversation.h"

class ChatRoom
{
public:
    explicit ChatRoom();
    explicit ChatRoom(QString roomId,QString admin);

    void setRoomID(QString nickName);
    QString getRoomId();
//    void setTitle();

    //대화저장
    int storeChat(const QString& chat,const QString& nickname,const QString& date);
    //방에 속하는 유저
    QStringList getRoomUserList();
    //특정 유저 체크
    bool isUserRoom(const QString& nickName);
    bool addUser(const QString& nickname);
    bool addUsers(const QString& nickname, const QString& delimiter = ",");
    bool removeUsers(const QString& nickname);
    
private:
    QString roomId;
    //QString title;//방 관계자 대화명
    QString admin;//방을 만든 User
    QStringList roomUserNames;//방에 있는 유저 리스트
    ChatConversation cc;//대화 내역

};

#endif // CHATROOM_H
