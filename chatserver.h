#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

#include "chatsocketmgr.h"

class ChatTransmit;
class ChatUserDataMgr;

class ChatServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit ChatServer(QObject *parent=nullptr);
    explicit ChatServer(ChatTransmit* ct, ChatUserDataMgr* cudm);

    QByteArray intToArray(qint32 source);
    void getMsgBody(QByteArray& Body, QByteArray str, qint16 strSize);
    void SetResMsg(const QString& protocol,QByteArray& resMsg,const QString& msg);//
    void SetResMsg(const QString& protocol,QByteArray& resMsg, QString& msg);//overroding

    void SetResFriendMsg(qint32 numOfFriendCount,const QString& protocol,QByteArray& resMsg, QByteArray& msg);



private slots:
    void readyRead(); //메시지 수신
    void disconnected(); // 접속 종료
    void sendUserList(); // 유저정보
   bool checkPassword(QString password); //비밀번호 검증

signals:
    void clients_signal(int users);//접속한 유저의 수 갱신
    void message_signal(QString msg);// ui에 출력될 메시지 정보 저장

protected:
    virtual void incomingConnection(qintptr socketfd);

private:
    QSet<QTcpSocket*> clients;//set을 구성하여 tcp 소켓을 키를 가짐
    QMap<QTcpSocket*,QString> users; // tcp 소켓을 키로 구성하여 String을 값으로 나타냄
    QMultiMap<QString, QString> friendList;//접속한 클라이언트의 친구 목록
    ChatTransmit* ct;
    ChatSocketMgr csm;
    ChatUserDataMgr* cudm;
};

#endif // CHATSERVER_H
