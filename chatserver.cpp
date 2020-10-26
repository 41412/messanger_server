#include <QtWidgets>
#include <QRegExp>
#include "chatserver.h"
#include "chatdata.h"
#include <QDebug>

ChatServer::ChatServer(QObject *parent)
    : QTcpServer(parent)
{
}

void ChatServer::incomingConnection(int socketfd)
{
    qDebug() << Q_FUNC_INFO;

    QTcpSocket *client = new QTcpSocket(this);
    client->setSocketDescriptor(socketfd);
    clients.insert(client);

    emit clients_signal(clients.count());

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
//                _________________________________________________________________________________________________
// 로그인 수신 메시지 패킷 : 메시지 길이(4byte)|프로토콜 (4byte)|" "(1byte)|NickName(lengh byte)|" "(1byte)|비밀번호(length byte)
//                _________________________________________________________________________________________________
//  로그인 요청 및 사용자 등록 요청의 메시지 길이
qint16 ChatServer::getMsgLength(QByteArray str)
{
    qint32 len = 0;

    for(qint8 i=0;i<4;i++)
    {
        //NULL인 경우 스킵
        if(str[i] == '\0')
        {
            continue;
        }
        len = (len*10) +(str[i]-'0');
    }

    return len;
}
// 로그인 요청 및 사용자 등록 요청의 메시지 내용 저장
//프로토콜(4byte) + 닉네임 + 비밀번호
void ChatServer::getMsgBody(QByteArray& Body,QByteArray str, qint16 strSize)
{
    qint8 idx = 0;

    for(qint8 i = 4;i<strSize;i++)
    {
        Body[idx++] = str[i];

    }
    Body[idx] = 0;



}
//로그인 및 등록 요청 시 응답 메시지 설정
//                _________________________________________________________________________________________________
// 로그인 응답 메시지 패킷 : 메시지 길이(4byte)|프로토콜 (4byte)|" "(1byte) | "Login Ok"(8byte)
//사용자 등록 응답 메시지 패킷 :                                                                                    "Enrollment Ok(13byte)"
//                _________________________________________________________________________________________________
//  로그인 요청 및 사용자 등록 요청의 메시지 길이

void ChatServer::SetResMsg(qint8 protocol,QByteArray& resMsg, const QString& msg)
{
    qint8 byte = 0;
    qint8 temp = msg.length()+2;


        //메시지 길이 정의
    for(byte = 3;byte >= 0;byte--)
    {
        if(temp != 0)
        {
            int remain = temp%10;

            resMsg[byte] = remain + '0';

            temp = temp/10;
        }
        else
        {
            resMsg[byte] = '\0';
        }
    }

    resMsg += ' ';
    resMsg += (protocol+'0');
    resMsg += ' ';
    resMsg += msg.toUtf8();

}


qint8 ChatServer::getProtocol(QByteArray msg)
{
    qint8 protocol;

    protocol = msg[0] - '0';

    return protocol;
}

void ChatServer::getPassWord(QByteArray& passWord,QByteArray msg)
{
    for(qint8 i = 7; i<msg.length();i++)
    {
        passWord+=msg[i];
    }
}

void ChatServer::readyRead()
{
    qDebug() << Q_FUNC_INFO;
    QTcpSocket *client = (QTcpSocket*)sender();


    QByteArray recvMsg = client->readAll();//클라이언트로 부터 메시지 수신

    qint8 recvMsgLen = recvMsg.length();

    qint8 msgBodyLen = getMsgLength(recvMsg);//클라이언트로 부터 수신 받은 메시지 내용의 길이
    QByteArray msgBody;//메시지 내용(길이 + 프로토콜 + 메시지 내용)
    getMsgBody(msgBody,recvMsg,recvMsgLen); // 메시지 내용 저장



     qDebug() << "msgBodyLen :" <<msgBodyLen<<'\n';

     qDebug() << "msgBody : " <<msgBody;

    // QString str = QString::fromLocal8bit(msgBody.data(),msgBody.length());

                //프로토콜 닉네임 비밀번호 정보를 각각 얻어옴
        qint8 protocol = getProtocol(msgBody);
        QString NickName = QString::fromUtf8(msgBody).trimmed();
        QByteArray PassWord;
        getPassWord(PassWord,msgBody);



                //닉네임, 비밀번호 출력
        QString str = QString("Read line: %1").arg(NickName);



        emit message_signal(str);


                //로그인 회원가입 응답
        QByteArray resMsg; //응답 메시지


                //회원 가입 등록 요청 (임시로  회원가입 등록 요청은 프로토콜 1로 설정(임시)
       if(protocol == 1)
       {
            qDebug() << "Enrollment User protocol number 2";

            if(checkPassword(PassWord) == 1)
            {
                SetResMsg(3,resMsg,"Password must be more than 4 letters.");
                client->write(resMsg);

                return;
            }
            else
            {
                SetResMsg(2,resMsg,"Enrollment OK");
                client->write(resMsg);
            }


          //  EnrollmentUser();

            //connect(client, SIGNAL(readyRead()), this,SLOT(readyRead()));
            return;
       }

        //로그인
       else if(protocol == 0)
       {
           qint32 ret = 0;

           SetResMsg(0,resMsg,"Login OK");


           //SetResMsg(2,resMsg,"Enrollment OK");
            //client->write(QString("Login OK").toUtf8());
            //ret = client->write(resMsg);
           ret = client->write(resMsg);

            qDebug() <<'\n'<< "retByte" <<ret<<"resMsg Size:"<<resMsg.size()<<'\n';


          QRegExp meRegex("^/me:(.*)$");

            if(meRegex.indexIn(NickName) != -1)
            {
                QString user = meRegex.cap(1);
                users[client] = user;
                foreach(QTcpSocket *client, clients)
                {
                   client->write(QString("서버: %1 접속").arg(user).toUtf8());
                }

                sendUserList();
            }
            else if(users.contains(client))
            {
                 QString message = NickName;
                 QString user = users[client];

                 QString str;
                 str = QString("유저명: %1, 메시지: %2").arg(user).arg(message);
                 emit message_signal(str);

                foreach(QTcpSocket *otherClient, clients)
                    otherClient->write(QString(user+":"+message+"\n").toUtf8());
            }
     }
}

void ChatServer::disconnected()
{
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

//////////////////////////////////////
/////////////////////////등록///////////////////////////////
/////////////////////////////////////
void ChatServer::EnrollmentUser(QString nickName,QString passWord)
{
    userinfo readUser;

    readUser.nickName = nickName;
    readUser.passWord = passWord;

    //userTable.push_back(readUser);


}



bool ChatServer::checkPassword(QString passWord) //비밀번호 검증
{
    if(passWord.length() < 4)
    {
        return 1;
    }

    return 0;
}
