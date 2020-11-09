#include "chatdataprotocol.h"
#include <QDataStream>

static const unsigned char signature[8]={0xff,0xee,'M','R','2','0','2','0'};

static QByteArray intToArray(qint32 source)
{
    // Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data(&temp, QIODevice::ReadWrite);
    data << source;

    return temp;
}



// 로그인 요청 및 사용자 등록 요청의 메시지 내용 저장
//프로토콜(4byte) + 닉네임 + 비밀번호
static void getMsgBody(QByteArray& Body,QByteArray str, qint16 strSize)
{
    qint8 idx = 0;

    for(qint8 i = 5;i<strSize;i++)
    {
        Body[idx++] = str[i];

    }
    Body[idx] = '\0';



}
//로그인 및 등록 요청 시 응답 메시지 설정
//                _________________________________________________________________________________________________
// 로그인 응답 메시지 패킷 : 메시지 길이(4byte)|프로토콜 (4byte)|" "(1byte) | "Login Ok"(8byte)
//사용자 등록 응답 메시지 패킷 :                                                                                    "Enrollment Ok(13byte)"
//                _________________________________________________________________________________________________
//  로그인 요청 및 사용자 등록 요청의 메시지 길이

static void SetResMsg(const QString& protocol,QByteArray& resMsg, const QString& msg)
{
    qint8 tempLen = protocol.length() + msg.length();


    //메시지 길이 정의
    resMsg.prepend(intToArray(tempLen));
    resMsg += ' ';

    resMsg.append(protocol.toUtf8());
    resMsg += ' ';
    resMsg += msg.toUtf8();

}

static void SetResMsg(const QString& protocol,QByteArray& resMsg, QString& msg)
{
    qint32 tempLen = protocol.length() + msg.length();



    //메시지 길이 정의
    resMsg.prepend(intToArray(tempLen));
    resMsg += ' ';

    resMsg.append(protocol.toUtf8());

    resMsg += ' ';

    resMsg += msg.toUtf8();

}

static void SetResFriendMsg(qint32 numOfFriendCount,const QString& protocol,QByteArray& resMsg, QByteArray& msg)
{

    qint32 tempLen = msg.length()+protocol.length();


    //메시지 길이 정의
    resMsg.prepend(intToArray(tempLen));
    resMsg += ' ';

    resMsg.append(protocol.toUtf8());
    resMsg += ' ';

    resMsg.append(intToArray(numOfFriendCount));
    resMsg += ' ';
    resMsg += msg;

}

QString ChatDataProtocol::extractProtocol(const QByteArray& message)
{
    qint32 idx = 0;
    QString str;

    for(idx=0;idx < message.length();idx++)
    {
        if(message.at(idx) == ' ')
        {

            break;
        }
        str+=message[idx];
    }

    return str;
}


static inline QByteArray fillHeader(const QByteArray& ar)
{
    QByteArray b;
    b.append(0xff);
    b.append(0xee);
    b.append("MR2020");
    b.append(intToArray(ar.length()));
    b += ar;
    return b;
}

QByteArray ChatDataProtocol::makeLoginRes(bool success)
{
    return fillHeader(success ? "LOGIN_SUCCESS" : "LOGIN_FAIL");
}

QByteArray ChatDataProtocol::makeResCreateRoom(const QString& id)
{
    QByteArray ba;
    // fill body
    ba = id.toStdString().c_str();

    return ba;
}

static int byteArrayToInt(const QByteArray& ba) {
    QByteArray baSize = ba.left(4);
    QDataStream ds(&baSize,QIODevice::ReadOnly);
    qint32 size=0;
    ds >> size;
    return size;
};

bool ChatDataProtocol::parseHeader(const QByteArray& message, bool& isValid, int& size)
{
    //TODO : find signature in entire message in future...
    isValid = false;
    size = 0;
    if (memcmp(message.constData(), signature, 8) == 0) {
        isValid = true;
        size = byteArrayToInt(message.mid(8,4));
        return true;
    }
    return false;
}






ChatDataProtocol::ChatDataProtocol(QObject *parent) : QObject(parent)
{

}

QMap<QString,QString> ChatDataProtocol::ReceiveProtocol(const QByteArray& message, QByteArray& extra)
{
    // 프로토콜과 메시지 바디를 포함한 message를 파라미터로 받는다.
    // messsage를 공백을 기준으로 분리한다.
    // 로그인 요청하는 프로토콜의 경우 분리한 데이터들을 아래와 같이 저장
    // map["ID"] = 프로토콜, map["닉네임"] = 닉네임명, map["비밀번호"] = 비밀번호명
    QMap<QString,QString> m;



    //signature 비교
    //메세지 프로토콜의 signature가 다른 경우
    if(memcmp(message.constData(),signature,8) != 0)
    {

        return m;
    }



    QByteArray baSize = message.mid(8,4);
    QDataStream ds(&baSize,QIODevice::ReadOnly);
    qint32 size=0;
    ds >> size;


    //메시지 사이즈 ds 사이즈 비교
    QByteArray body = message.mid(12);
    QString pid = extractProtocol(body);

    if (pid == "REQUEST_SUBMIT" || pid == "REQUEST_LOGIN") {
        QStringList tokens = QString::fromUtf8(body).split(" ");
        m["target"] = "login";
        m["id"] = pid;
        if (tokens.size() == 3) {
            m["nickname"] = tokens[1];
            m["password"] = tokens[2];
        }
        else {
            // nothing
        }
    }// end if("REQUEST_SUBMIT" || "REQUEST_LOGIN")

    else if (pid =="REQUEST_CREATE_CHATROOM" )
    {

    }

    else if(pid =="REQUEST_INVITE_USER")
    {

    }
    else if(pid == "REQUEST_LEAVE_CHATROOM")
    {

    }

#if 0
    QTcpSocket *client = (QTcpSocket*)sender();


    QByteArray recvMsg = client->readAll();//클라이언트로 부터 메시지 수신
    //수신 메시지 총 길이
    qint32 recvMsgLen = recvMsg.length();


    QByteArray msgBody;//메시지 내용(프로토콜 + 메시지 내용)
    getMsgBody(msgBody,recvMsg,recvMsgLen); // 메시지 내용 저장


    //메시지 분리 (길이 , 프로토콜)
    QStringList length_protocol = QString(msgBody).split(" ");


    QString protocolType = length_protocol[0];
    QString NickName;

    //response message
    QByteArray resMsg; //응답 메시지




    qDebug() << "msgBody : " <<msgBody;

    // 회원가입 || 로그인

    if(protocolType == "REQUEST_SUBMIT" || protocolType == "REQUEST_LOGIN")
    {
        //프로토콜 닉네임 비밀번호 정보를 각각 얻어옴
        QStringList protocol_nickname_password = QString(msgBody).split(" ");
        QString protocol = protocol_nickname_password[0];
        NickName = protocol_nickname_password[1];
        QString PassWord = protocol_nickname_password[2];


        qDebug() <<'\n'<< "protocol : " << protocol << "NickName : " << NickName << "PassWord :"<< PassWord;
        //닉네임, 비밀번호 출력
        QString str = QString("Read line: %1 %2").arg(NickName).arg(PassWord);


        emit message_signal(str);




        //회원 가입 등록 요청
        if(protocol == "REQUEST_SUBMIT")
        {
            qDebug() << "Enrollment User protocol number ";

            if(checkPassword(PassWord) == 1)
            {
                SetResMsg("SUBMIT_FAIL",resMsg,"Password must be more than 4 letters.");
                client->write(resMsg);

                return;
            }
            else
            {

                //메신저에 가입된 모든 유저들 관리하는 객체
                UserInfoMgr userMgr(NickName,PassWord);



                //기존에 닉네임이 존재하는 경우 등록 불가
                if(userMgr.isExistName(NickName))
                {
                    SetResMsg("SUBMIT_FAIL",resMsg,"nickName Existed");
                    client->write(resMsg);

                    return;

                }


                userMgr.setUserInfo(NickName,PassWord);




                SetResMsg("SUBMIT_SUCCESS",resMsg,"Enrollment OK");
                client->write(resMsg);
            }


            return;
        }

        //로그인
        else if(protocol == "REQUEST_LOGIN")
        {
            qint32 ret = 0;


            SetResMsg("LOGIN_SUCCESS",resMsg,"Login OK");

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


            }
        }//end : else if (로그인)
    }//end if(protocol == 0 || protocol == 1)
    else if(protocolType == "REQUEST_USERDATA") //추후 변경
    {

        qDebug() <<'\n'<< "enter protocolType 2";

        //데이터 요청 메시지 수신
        //길이_프로토콜

        recvMsg = client->readAll();

        //프로토콜 닉네임 비밀번호 정보를 각각 얻어옴

        QStringList protocol_nickname = QString(msgBody).split(" ");
        QString protocol = protocol_nickname[0];
        NickName = protocol_nickname[1];

        qDebug() << "protocol = " << protocol << "NickName = " << NickName;


        //메시지 START 전달
        SetResMsg("USERDATA_SEND_START",resMsg,"");
        client->write(resMsg);
        //resMsg 초기화
        resMsg.clear();
        ///////////////////////////////////////////////////////////////


    }// end if protocol ==  (데이터 전송 요청)

    else if(protocolType == "READY_TO_RECEIVE")
    {

        resMsg.clear();

        QByteArray copyFriend;
        qint32 friendCnt = 0; //친구 목록 수

        friendList.insert(NickName,"Lee");
        friendList.insert(NickName,"Park");
        friendList.insert(NickName,"Choi");

        //메시지 형태로 "이름1 이름2 이름3" 공백을 기준으로 하여 클라이언트에게 전송
        QList<QString> friendNickNameList = friendList.values(NickName);


        friendNickNameList.count();

        int tempCnt = 0;
        foreach(QString friendName,friendNickNameList )
        {

            copyFriend += friendName.toStdString().c_str();


            if(tempCnt == friendCnt-1)
            {
                break;
            }

            copyFriend +=' ';

        }


        SetResFriendMsg(friendCnt,"SEND_FRIENDLIST",resMsg,copyFriend);
        qDebug() << "friend List resMsg :"<<resMsg;


        client->write(resMsg);

        //friendList의 버퍼를 비움
        friendList.clear();
        ////////////////////////////////////////////////////////////////////////////
        //친구 목록 수신 완료 응답
        //클라이언트로부터 받은 메시지의 프로토콜 체크
        ///////////////////////////////////////////////////////////////////////////////
        //클라이언트에게 방 정보 전달








    }//end : READY_TO_RECEIVE
#endif





    return m;
}




