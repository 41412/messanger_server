#include "chatloginmgr.h"
#include "chatdataprotocol.h"
#include "userinfomgr.h"
#include <QString>
#include <QDebug>



ChatLoginMgr::ChatLoginMgr(UserInfoMgr* uim)
    :uim(uim)
{

}

bool ChatLoginMgr::checkPassword(const QString& password)
{
    if(password.length() < 4)
    {
        return false;
    }

    return true;
}

void ChatLoginMgr::process(const QMap<QString,QString>& mp,const QByteArray& extradata,BaseSessionProxy* sp)
{
    if (!mp.contains("id")) { return; }

    if(mp["id"] == "REQUEST_SUBMIT")
    {
        QString nickName = mp["nickname"];
        QString password = mp["password"];

        //기존에 있는 닉네임인지 확인
        //확인하여 기존에 있는 닉네임 이면 등록 불가
        if(uim->isExistName(nickName) == true)
        {
            //이미 존재하는 닉네임 이므로
            //클라이언트에게 등록 요청 불가 메시지 전달
            sp->send(ChatDataProtocol::makeLoginRes(false));
        }
        else
        {
            //등록할 수 있는 닉네임이므로
            //클라이언트에게 등록 요청 허가 메시지 전달
            sp->send(ChatDataProtocol::makeLoginRes(true));

        }
    }

    if(mp["id"] == "REQUEST_LOGIN")
    {
        QString nickName = mp["nickname"];
        QString password = mp["password"];

        QMap<QString,QString> arg;
        arg["cmd"] = "login.session_started";
        arg["nickname"] = nickName;
        sp->doWork(arg);

        // check log in & password
        // 비밀번호가 유효하지 않거나 이미 로그인 되어있는 경우
        //
        if(checkPassword(password) == false)
        {

        }

        // make packet
        QByteArray res = ChatDataProtocol::makeLoginRes(true);
        sp->send(res);

        qDebug() << "REQUEST_LOGIN matched";
    }
    else
    {
        qDebug() << "REQUEST_LOGIN not matched";
    }

}
