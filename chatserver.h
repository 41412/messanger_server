#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

class ChatServer : public QTcpServer
{
    Q_OBJECT

public:
    ChatServer(QObject *parent=0);

    qint16 getMsgLength(QByteArray str);
    void getMsgBody(QByteArray& Body, QByteArray str, qint16 strSize);
    void SetResMsg(qint8 protocol,QByteArray& resMsg,const QString& msg);
    qint8 getProtocol(QByteArray msg);
    void EnrollmentUser(QString nickName,QString passWord);
    void getPassWord(QByteArray& passWord,QByteArray msg);

private slots:
    void readyRead(); //메시지 수신
    void disconnected(); // 접속 종료
    void sendUserList(); // 유저정보
  //  void UserListInfo(); // 접속한 유저들의 정보 저장 (좀 더 고민)
   bool checkPassword(QString password); //비밀번호 검증

signals:
    void clients_signal(int users);//접속한 유저의 수 갱신
    void message_signal(QString msg);// ui에 출력될 메시지 정보 저장

protected:
    void incomingConnection(int socketfd);

private:
    QSet<QTcpSocket*> clients;//set을 구성하여 tcp 소켓을 키를 가짐
    QMap<QTcpSocket*,QString> users; // tcp 소켓을 키로 구성하여 String을 값으로 나타냄

};

#endif // CHATSERVER_H
