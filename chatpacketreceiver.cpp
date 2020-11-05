#include "chatpacketreceiver.h"
#include "chatdataprotocol.h"

ChatPacketReceiver::ChatPacketReceiver()
{

}
int ChatPacketReceiver::process(const QByteArray& ba)
{
    //1. 메시지의 패킷 헤더 체크
    //2. 헤더가 있는 경우
    //  2-1. buffer에 ba 내용 카피 및 사이즈 저장
    //  2-2.  buffer 지우기
    //3. 헤더가 없는 경우
    //3-1. buffer에 ba 내용 카피

    bool validPacket = false;
    int sizePacket = 0;
    buffer += ba;

    while (buffer.size() != 0)
    {
        if (ChatDataProtocol::parseHeader(buffer, validPacket, sizePacket)) {
            int realSize = sizePacket + ChatDataProtocol::getHeaderSize();
            if (buffer.size() >= realSize) {
                packets += buffer.left(realSize);
                buffer.remove(0, realSize);
            }
            else {
                packets += buffer;
                remainSize = realSize - buffer.size();
                buffer.clear();
            }
        }
        else {
            if (remainSize > 0 && packets.size() > 0) {
                if (buffer.size() <= remainSize) {
                    packets.last() += buffer;
                    remainSize -= buffer.size();
                    buffer.clear();
                }
                else {
                    packets.last() += buffer.left(remainSize);
                    buffer.remove(0, remainSize);
                    remainSize = 0;
                }
            }
            else {
                qDebug("has wrong data");
                buffer.clear();
            }
        }
    }
    return packets.size();
}

QByteArray ChatPacketReceiver:: getPacket()
{
    QByteArray a;
    if (!packets.isEmpty()) {
        a = packets.front();
        packets.pop_front();
    }
    return a;
}

int ChatPacketReceiver::getPacketCount()
{
    return packets.count();
}
