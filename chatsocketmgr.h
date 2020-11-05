#ifndef CHATSOCKETMGR_H
#define CHATSOCKETMGR_H

#include <QMap>
#include <QSet>
class ChatSession;

class ChatSocketMgr
{
public:
    ChatSocketMgr();
    void addSession(ChatSession* socket);
    void removeSession(ChatSession* socket);
    //매핑
    void setSessionUser(ChatSession* sockdet,const QString& nickname);
    ChatSession* get(const QString& nickname);

    //소켓 객체 가져오기
private:
    QMap<QString,ChatSession*> mp;
    QSet<ChatSession*> st;

};

#endif // CHATSOCKETMGR_H
