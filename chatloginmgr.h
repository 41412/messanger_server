#ifndef CHATLOGINMGR_H
#define CHATLOGINMGR_H
#include <QByteArray>
#include <QMap>
#include <basesessionproxy.h>
//#include "userinfomgr.h"

class UserInfoMgr;

class ChatLoginMgr
{

public:
    explicit ChatLoginMgr(UserInfoMgr* uim);
    void process(const QMap<QString,QString>& mp,const QByteArray& extraData,BaseSessionProxy* sp);
    bool checkPassword(QString password);

private:
    UserInfoMgr* uim;
};

#endif // CHATLOGINMGR_H
