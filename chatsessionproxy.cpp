#include "chatsessionproxy.h"


ChatSessionProxy::ChatSessionProxy(ChatSocketMgr* csm,QTcpSocket* socket,ChatUserDataMgr* cudm)
    :csm(csm),socket(socket),cudm(cudm)
{

}
void ChatSessionProxy::doWork(const QMap<QString,QString>& m)
{
    if (m["cmd"] == "login.new_user") {
        //m["nickname"], m["password]
        // cudm->addNewUser(...
    }
    else if (m["cmd"] == "login.session_started") {
        csm->setSocketUser(socket, m["nickname"]);
    }
}

void ChatSessionProxy::send(const QByteArray& ba)
{
    // socket->write(ba);
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
