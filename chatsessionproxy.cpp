#include "chatsessionproxy.h"
#include "chatsocketmgr.h"
#include "chatsession.h"

ChatSessionProxy::ChatSessionProxy(ChatSocketMgr* csm,ChatSession* cs,ChatUserDataMgr* cudm)
    :csm(csm),cs(cs),cudm(cudm)
{

}
void ChatSessionProxy::doWork(const QMap<QString,QString>& m)
{
    if (m["cmd"] == "login.new_user") {
        //m["nickname"], m["password]
        // cudm->addNewUser(...
    }
    else if (m["cmd"] == "login.session_started") {
        csm->setSessionUser(cs, m["nickname"]);
    }
}

void ChatSessionProxy::send(const QByteArray& ba)
{
    if (cs->isWritable()) {
        cs->write(ba);
    }
}

void ChatSessionProxy::send(const QStringList& userlist, const QByteArray& ba)
{
    // loop
    // find socket object by user name
    // write
}

void ChatSessionProxy::updateUserData(const QString& user, const QMap<QString,QString>& m)
{

}

ChatPacketReceiver* ChatSessionProxy::getPacketReceiver()
{
    return cs->getReceiver();
}

