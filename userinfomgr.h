#ifndef USERINFOMGR_H
#define USERINFOMGR_H


#include "widget.h"
#include "chatserver.h"
#include "chatdata.h"
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
    explicit UserInfoMgr(QString nickName,QString passWord);

    bool isExistName(const QString& nickName);
    void setUserInfo(QString nickName,QString passWord);
    void totalUser();

signals:
 void message_signal(QString msg);// ui에 출력될 메시지 정보 저장
public slots:

private:
    QVector<userinfo> userTable;
    QString nickName;
    QString passWord;


};


#endif // USERINFOMGR_H
