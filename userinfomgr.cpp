#include "userinfomgr.h"
#include <QtWidgets>
#include <QRegExp>
#include "chatserver.h"
#include "chatdata.h"
#include "userinfomgr.h"
#include "widget.h"
#include <QDebug>


UserInfoMgr::UserInfoMgr(QObject *parent) :
    QObject(parent)
{

}
UserInfoMgr::UserInfoMgr(QString nickName,QString password)
{
    this->nickName = nickName;
    this->passWord = password;
}


void UserInfoMgr::setUserInfo(QString nickName,QString passWord)
{
    UserInfoMgr::userinfo tempUser;

    tempUser.nickName = nickName;
    tempUser.passWord = passWord;

    userTable.push_back(tempUser);


}


bool UserInfoMgr::isExistName(const QString& nickName)
{
    QVector<UserInfoMgr::userinfo>::iterator iter;

    for(iter = userTable.begin();iter != userTable.end();iter++)
    {
       if(iter->nickName == nickName)
       {
           return true;
       }
    }


    return false;
}

//모든 접속자 조회
void  UserInfoMgr::totalUser()
{
    QVector<UserInfoMgr::userinfo>::iterator iter;

    for(iter = userTable.begin();iter != userTable.end();iter++)
    {
        QString str = QString("nickName : %1").arg(nickName);
        qDebug() << "nickName :"<<iter->nickName <<"password" <<iter->passWord<<'\n';
        emit message_signal(str);
    }
}
