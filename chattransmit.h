#ifndef CHATTRANSMIT_H
#define CHATTRANSMIT_H

#include <QObject>
#include "chatfriendmgr.h"
#include "chatloginmgr.h"
#include "chatroommgr.h"
#include "chatsessiondata.h"
#include "chatdataprotocol.h"

class ChatTransmit : public QObject
{
    Q_OBJECT
public:
    explicit ChatTransmit(QObject *parent = nullptr);
    explicit ChatTransmit(ChatRoomMgr* rm,ChatLoginMgr* lm,ChatFriendMgr* fm);

    void process(ChatSessionData* data);


private:
    ChatDataProtocol dataprotocol;
    ChatRoomMgr* rm;
    ChatLoginMgr* lm;
    ChatFriendMgr* fm;

};

#endif // CHATTRANSMIT_H
