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

    static QByteArray makeLoginRes(bool succese);

private:
    QMap<QString,QByteArray> messageMap;
};

#endif // CHATDATAPROTOCOL_H
