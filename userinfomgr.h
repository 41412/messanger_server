#ifndef USERINFOMGR_H
#define USERINFOMGR_H

#include <QObject>


class UserInfoMgr : public QObject
{
    Q_OBJECT
public:
    typedef struct _userinfo
    {
        QString nickName;
        QString passWord;
    }userinfo;

    explicit UserInfoMgr(QObject *parent = 0);

    bool isExistName(const QString& nanme);

signals:

public slots:

private:
    //QVector<userinfo> _table;

};

#endif // USERINFOMGR_H
