#ifndef CHATLOGINMGR_H
#define CHATLOGINMGR_H
#include <QByteArray>
#include <QMap>
#include <basesessionproxy.h>

class ChatLoginMgr;
class UserInfoMgr;

class ChatLoginMgr
{

public:
    explicit ChatLoginMgr(UserInfoMgr* uim);
    void process(const QMap<QString,QString>& mp,const QByteArray& extraData,BaseSessionProxy* sp);
    bool checkPassword(const QString& password);

private:
    UserInfoMgr* uim;
};

#endif // CHATLOGINMGR_H
