#ifndef CHATROOMMGR_H
#define CHATROOMMGR_H

#include <QObject>
#include "basesessionproxy.h"

class ChatRoomMgr : public QObject
{
    Q_OBJECT
public:
    explicit ChatRoomMgr(QObject *parent = nullptr);
    void process(const QMap<QString,QString>& mp,const QByteArray& extradata,BaseSessionProxy* sp);
signals:

};

#endif // CHATROOMMGR_H
