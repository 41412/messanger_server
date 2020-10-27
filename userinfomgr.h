#ifndef USERINFOMGR_H
#define USERINFOMGR_H

#include <QObject>
#include <QVector>
#include <QDebug>

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

    bool isExistName(const QString& nickName);
    void setUserInfo(QString nickName,QString passWord);
    void attendUser();

signals:

public slots:

private:
   QVector<userinfo> userTable;

};


#endif // USERINFOMGR_H
