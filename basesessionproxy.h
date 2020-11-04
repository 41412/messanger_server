#ifndef BASESESSIONPROXY_H
#define BASESESSIONPROXY_H

#include <QObject>

class BaseSessionProxy : public QObject
{
    Q_OBJECT
public:
    explicit BaseSessionProxy(QObject *parent = nullptr);
    virtual void doWork(const QMap<QString, QString>& ){}
    virtual void send(const QByteArray& ){}
    virtual void send(const QStringList& , const QByteArray& ){}
    virtual void updateUserData(const QString& , const QMap<QString,QString>& ){}

signals:

};

#endif // BASESESSIONPROXY_H
