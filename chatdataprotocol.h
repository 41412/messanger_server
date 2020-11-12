#ifndef CHATDATAPROTOCOL_H
#define CHATDATAPROTOCOL_H

#include <QObject>
#include <QMap>

class ChatDataProtocol : public QObject
{
    Q_OBJECT
public:
    explicit ChatDataProtocol(QObject *parent = nullptr);
    QMap<QString,QString> ReceiveProtocol(const QByteArray& message, QByteArray& extra);
    static QString extractProtocol(const QByteArray& message);

    static bool parseHeader(const QByteArray& message, bool& isValid, int& size);
    static int getHeaderSize() { return 12; }

    static QByteArray makeLoginRes(bool succese);
    static QByteArray makeResCreateRoom(const QString& id);

    static QByteArray makeSendStart();
    static QByteArray makeSendEnd();

    static QByteArray makeSendFriendList(const QStringList& friendList);
    //static QByteArray makeSendChatRoomList(const QStringList& roomlist, void (*filler)(const QString&,QStringList&));
    static QByteArray makeSendChatRoomList(const QStringList& roomlist, std::function<void(const QString&,QStringList&)> callback);

    static QByteArray makeResUpdateChat(const QString& roomid,const QString& user,const QString& timestamp,int index,const QString& message);
    static QByteArray makeResLeaveRoom(const QString& roomid,const QString& user);
private:
    QMap<QString,QByteArray> messageMap;
};

#endif // CHATDATAPROTOCOL_H
