#ifndef CHATTRANSMIT_H
#define CHATTRANSMIT_H

#include <QObject>
#include "chatloginmgr.h"
#include "chatsessiondata.h"
#include "chatdataprotocol.h"
#include "chatuserdatamgr.h"

class ChatTransmit : public QObject
{
    Q_OBJECT
public:
    explicit ChatTransmit(QObject *parent = nullptr);
    explicit ChatTransmit(ChatLoginMgr* lm,ChatUserDataMgr* chatuserdatamgr);

    void process(ChatSessionData* data);


private:
    ChatDataProtocol dataprotocol;
    ChatLoginMgr* lm;
    ChatUserDataMgr* cudm;

};

#endif // CHATTRANSMIT_H
