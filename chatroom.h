#ifndef CHATROOM_H
#define CHATROOM_H

#include <QObject>
#include <QTime>

class chatRoom : public QObject
{
    Q_OBJECT

public:
    explicit chatRoom(QObject *parent = 0);
    explicit chatRoom(QString roomId,QString title,QString admin);


    void setRoomID(QString nickName);
    QString getRoomId();
    void setTitle();





signals:

public slots:
    
private:
    QString roomId;
    QString title;//방 관계자 대화명
    QString admin;//방을 만든 User
    QList<QString> roomUserName;//방에 있는 유저 리스트

};

#endif // CHATROOM_H
