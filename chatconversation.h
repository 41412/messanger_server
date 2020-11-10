#ifndef CHATCONVERSATION_H
#define CHATCONVERSATION_H

#include <QObject>

class ChatConversation : public QObject
{
    Q_OBJECT

public:
    typedef struct _chat
    {
        QString date;
        QString fromUser;
        QString message;
    }Chat;

    explicit ChatConversation(QObject *parent = 0);
    //조회
    QStringList queryChat(const QString& date,qint32 count);
    //추가
    int addChat(const QString& date,const QString& fromUser,const QString& message);

private:
    QVector<Chat> vt;

};

#endif // CHATCONVERSATION_H
