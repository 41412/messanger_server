#include "chatsocketmgr.h"
#include "chatsession.h"
#include <QDebug>
ChatSocketMgr::ChatSocketMgr()
{

}

void ChatSocketMgr::addSession(ChatSession* socket)
{
    //set의 키에 소켓 주소 저장
    st.insert(socket);

    qDebug() << "소켓 저장 :" << socket;
}
void ChatSocketMgr::removeSession(ChatSession* socket)
{
    QMap<QString,ChatSession*>::iterator iter;

    for(iter = mp.begin(); iter != mp.end();iter++)
    {
        if(iter.value() == socket)
        {
            mp.remove(iter.key());
            break;
        }
    }

    st.remove(socket);

}

void ChatSocketMgr::setSessionUser(ChatSession* socket,const QString& nickname)
{
    //set에서 주소가 기존에 있는지 확인
    //없으면 fail, 있으면 지우기
    //map의 닉네임(키)에 대응되는 주소 삽입

    if(st.find(socket) != st.end() )
    {
        st.remove(socket);
    }
    mp[nickname] = socket;

    qDebug() << "set nickname for a socket!!!  " << QString::asprintf("%X", mp[nickname]);
}
ChatSession* ChatSocketMgr::get(const QString& nickname)
{
    //이 이름이 없는 경우
    if(mp.find(nickname) == mp.end())
    {
        return nullptr;
    }

    return mp[nickname];
}
