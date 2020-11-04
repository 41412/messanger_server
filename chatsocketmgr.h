#ifndef CHATSOCKETMGR_H
#define CHATSOCKETMGR_H

#include <QTcpSocket>
#include <QMap>

class ChatSocketMgr
{
public:
    ChatSocketMgr();
    void addTcpSocket(QTcpSocket* socket);
    void removeTcpSocket(QTcpSocket* socket);
    //매핑
    void setSocketUser(QTcpSocket* sockdet,const QString& nickname);
    QTcpSocket* get(const QString& nickname);

    //소켓 객체 가져오기
private:
    QMap<QString,QTcpSocket*> mp;
    QSet<QTcpSocket*> st;

};

#endif // CHATSOCKETMGR_H
