#ifndef CHATROOM_H
#define CHATROOM_H

#include <QObject>

class chatRoom : public QObject
{
    Q_OBJECT
public:
    explicit chatRoom(QObject *parent = 0);

signals:

public slots:

};

#endif // CHATROOM_H
