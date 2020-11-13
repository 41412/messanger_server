#ifndef CHATUSERDATA_H
#define CHATUSERDATA_H

#include <QObject>
#include <QSet>

//방ID 및 다수의 닉네임 저장
class ChatUserData
{
public:

    explicit ChatUserData(const QString& nickname);

    QString getNickName();
    //닉네임에 매핑 되는 다수의 방 ID && 다수의 친구 닉네임
    int storeUserData(const QString& roomid,const QString& friendName);
    QStringList getFriendList();
    bool addFriend(const QString& nickname);
    bool removeFriend(const QString& nickname);
    int  getCountFriend();
    void load();
private:
    QString nickname;
    QSet<QString> friendlist;
};

#endif // CHATUSERDATA_H
