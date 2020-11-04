#include <QtWidgets>
#include <QRegExp>
#include "chatserver.h"
#include "chatdata.h"
#include "userinfomgr.h"
#include "widget.h"
#include "chatsessionproxy.h"
#include <QTcpSocket>
#include <QDebug>

#include "chattransmit.h"
#include "chatuserdatamgr.h"


ChatServer::ChatServer(QObject *parent)
    : QTcpServer(parent)
{
}

ChatServer::ChatServer(ChatTransmit* ct, ChatUserDataMgr* cudm)
    : QTcpServer(),ct(ct),cudm(cudm)
{
}

void  ChatServer::incomingConnection(qintptr socketfd)
{
    qDebug() << Q_FUNC_INFO;

    QTcpSocket *client = new QTcpSocket();
    client->setSocketDescriptor(socketfd);
    csm.addTcpSocket(client);

    //emit clients_signal(clients.count());

    QString str;
    str = QString("새로운 접속자: %1")
            .arg(client->peerAddress().toString());

    // client->write("0");

    emit message_signal(str);

    connect(client, SIGNAL(readyRead()), this,
            SLOT(readyRead()));
    connect(client, SIGNAL(disconnected()), this,
            SLOT(disconnected()));


}


void ChatServer::readyRead()
{
    qDebug() << Q_FUNC_INFO;


    QTcpSocket *client = (QTcpSocket*)sender();
    ChatSessionProxy csp(&csm,client,cudm);
    ChatSessionData csd(client->readAll(),&csp);

    ct->process(&csd);


}

void ChatServer::disconnected()
{
    QTcpSocket *client = reinterpret_cast<QTcpSocket*>(sender());
    QString str= QString("접속자 연결 종료 :: %1").arg(client->peerAddress().toString());

    emit message_signal(str);

    csm.removeTcpSocket(client);

   #if 0
    QTcpSocket *client = (QTcpSocket*)sender();

    QString str;
    str = QString("접속자 연결 종료 :: %1")
            .arg(client->peerAddress().toString());

    emit message_signal(str);

    clients.remove(client);

    emit clients_signal(clients.count());

    QString user = users[client];
    users.remove(client);

    sendUserList();
    foreach(QTcpSocket *client, clients)
        client->write(QString("서버: %1 접속종료").arg(user).toUtf8());
#endif
}

void ChatServer::sendUserList()
{

    QStringList userList;
    foreach(QString user, users.values())
        userList << user;

    foreach(QTcpSocket *client, clients)
        client->write(QString("/유저:" + userList.join(",") + "\n")
                      .toUtf8());
}


bool ChatServer::checkPassword(QString passWord) //비밀번호 검증
{
    if(passWord.length() < 4)
    {
        return 1;
    }

    return 0;
}
