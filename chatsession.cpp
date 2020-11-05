#include "chatsession.h"

ChatSession::ChatSession()
{

}

ChatSession::~ChatSession() {

}

ChatPacketReceiver* ChatSession::getReceiver()
{
    return &cpr;
}


