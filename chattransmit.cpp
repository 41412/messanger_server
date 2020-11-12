#include "chattransmit.h"


ChatTransmit::ChatTransmit(QObject *parent) : QObject(parent)
{

}
ChatTransmit::ChatTransmit(ChatLoginMgr* lm,ChatUserDataMgr* cudm)
    :QObject(),lm(lm),cudm(cudm)
{



}


void ChatTransmit::process(ChatSessionData* data)
{
    QMap<QString,QString > mp;
    QByteArray extra;
    ChatPacketReceiver* cpr = data->getProxy()->getPacketReceiver();

    if(cpr == nullptr)
    {
        //에러

    }
    else
    {
        // size 분석 후에 실제 데이터 사이즈와 비교 완전히 받을 때까지 데어터 수집
        // 완전히 준비되면 receiveProtocol 호출
        int count = cpr->process(data->data);
        while (count--) {
            QByteArray d = cpr->getPacket();

            //0. 프로토콜에 데이터 넘김
            mp = dataprotocol.ReceiveProtocol(d, extra);

            //1. 해당하는 프로토콜에 로그인 매니저로 프로토콜 확인
            // if (mp["target"] == "login")
            lm->process(mp, extra, data->getProxy());
            cudm->process(mp, extra, data->getProxy());

        }
    }
}
