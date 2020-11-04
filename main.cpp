#include <QApplication>
#include "widget.h"
#include "userinfomgr.h"
#include "chattransmit.h"
#include "chatdataprotocol.h"
#include "chatfriendmgr.h"
#include "chatloginmgr.h"
#include "chatroommgr.h"
#include "chatsessiondata.h"
#include "chatuserdatamgr.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    UserInfoMgr userinfomgr;
    ChatRoomMgr chatroommgr;
    ChatLoginMgr chatloginmgr(&userinfomgr);
    ChatFriendMgr chatfriendmgr(&userinfomgr);
    ChatUserDataMgr chatuserdatamgr;


    ChatTransmit chattransmit(&chatroommgr,&chatloginmgr,&chatfriendmgr);
    ChatServer server(&chattransmit,&chatuserdatamgr);


    QObject::connect(&server, SIGNAL(clients_signal(int)), &w,SLOT(slot_clients(int)));
    QObject::connect(&server, SIGNAL(message_signal(QString)), &w,SLOT(slot_message(QString)));
    //QObject::connect(ui->UserButton,&QPushButton::clicked,this,&Widget::slot_UserButton);


    server.listen(QHostAddress::Any, 35000);

    w.setWindowTitle("로그인 서버");
    w.show();



    return a.exec();
}
