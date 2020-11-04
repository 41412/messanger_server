#include "chatsessiondata.h"

ChatSessionData::ChatSessionData(QObject *parent) : QObject(parent)
{

}
ChatSessionData::ChatSessionData(const QByteArray& ba,BaseSessionProxy* bsp)
    : QObject(),data(ba),bsp(bsp)
{

}
