#ifndef CHATROOM_H
#define CHATROOM_H

#include <QObject>

class chatRoom : public QObject
{
    Q_OBJECT
public:
    explicit chatRoom(QObject *parent = 0);
    QString setRoomId()
    {

    }


signals:

public slots:

private:
    QString roomId;
    QString title;//방 관계자 대화명
    bool roomState;//관계자 방 표시 여부
    qint32 roomUserCount;



};

#endif // CHATROOM_H
