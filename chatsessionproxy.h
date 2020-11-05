#ifndef CHATSESSIONPROXY_H
#define CHATSESSIONPROXY_H

#include "chatuserdatamgr.h"
#include "basesessionproxy.h"
#include <QMap>
#include <QString>

class ChatSession;
class ChatSocketMgr;

class ChatSessionProxy : public BaseSessionProxy
{

public:
    explicit ChatSessionProxy(ChatSocketMgr* csm,ChatSession* cs,ChatUserDataMgr* cudm);
    virtual void doWork(const QMap<QString, QString>& m) override;
    virtual void send(const QByteArray& ba) override;
    virtual void send(const QStringList& userlist, const QByteArray& ba) override;
    virtual void updateUserData(const QString& user, const QMap<QString,QString>& m) override;
    virtual ChatPacketReceiver* getPacketReceiver() override;

private:
    ChatSocketMgr* csm;
    ChatSession * cs;
    ChatUserDataMgr* cudm;

};

#endif // CHATSESSIONPROXY_H
