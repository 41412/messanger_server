#ifndef CHATSESSIONPROXY_H
#define CHATSESSIONPROXY_H

#include "basesessionproxy.h"
#include "chatsocketmgr.h"
#include "chatuserdatamgr.h"
#include <QTcpSocket>

class ChatSessionProxy : public BaseSessionProxy
{

public:
    explicit ChatSessionProxy(ChatSocketMgr* csm,QTcpSocket* socket,ChatUserDataMgr* cudm);
    virtual void doWork(const QMap<QString, QString>& m) override;
    virtual void send(const QByteArray& ba) override;
    virtual void send(const QStringList& userlist, const QByteArray& ba) override;
    virtual void updateUserData(const QString& user, const QMap<QString,QString>& m) override;
private:
    ChatSocketMgr* csm;
    QTcpSocket* socket;
    ChatUserDataMgr* cudm;

};

#endif // CHATSESSIONPROXY_H
