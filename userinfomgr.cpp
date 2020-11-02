#include "userinfomgr.h"



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
void UserInfoMgr::totalUser()
{
    QVector<UserInfoMgr::userinfo>::iterator iter;

    for(iter = userTable.begin();iter != userTable.end();iter++)
    {
        qDebug() << "nickName :"<<iter->nickName <<"password" <<iter->passWord<<'\n';
    }
}
