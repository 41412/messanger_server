#include "chatconversation.h"
#include<QDebug>

 ChatConversation::ChatConversation(QObject *parent): QObject(parent)
 {

 }
 //조회
QStringList ChatConversation::queryChat(const QString& date,qint32 count)
{

}


//추가
void ChatConversation::addChat(const QString& date,const QString& fromUser,const QString& message)
{
    Chat temp;


    temp.date = date;
    temp.fromUser = fromUser;
    temp.message = message;

    vt.push_back(temp);
    qDebug() << __FUNCTION__ << "TestCode";


}
