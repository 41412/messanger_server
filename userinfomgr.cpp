#include "userinfomgr.h"

UserInfoMgr::UserInfoMgr(QObject *parent) :
    QObject(parent)
{

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



    return false;
}

//현재 접속자 조회
void UserInfoMgr::attendUser()
{
    QVector<UserInfoMgr::userinfo>::iterator iter;

    for(iter = userTable.begin();iter != userTable.end();iter++)
    {
        qDebug() << "nickName :"<<iter->nickName <<"password" <<iter->passWord<<'\n';
    }
}
