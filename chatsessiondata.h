#ifndef CHATSESSIONDATA_H
#define CHATSESSIONDATA_H

#include <QObject>
#include "basesessionproxy.h"

class ChatSessionData : public QObject
{
    Q_OBJECT
public:
    explicit ChatSessionData(QObject *parent = nullptr);
    explicit ChatSessionData(const QByteArray& ba,BaseSessionProxy* bsp);
    BaseSessionProxy* getProxy()
    {
        return bsp;
    }
    QByteArray data;


signals:

private:
    BaseSessionProxy* bsp;
};

#endif // CHATSESSIONDATA_H
