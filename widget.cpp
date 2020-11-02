#include "widget.h"
#include "chatserver.h"
#include "ui_widget.h"
#include "chatdata.h"
#include "userinfomgr.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);

    server = new ChatServer();
    connect(server, SIGNAL(clients_signal(int)), this,SLOT(slot_clients(int)));
    connect(server, SIGNAL(message_signal(QString)), this,SLOT(slot_message(QString)));
    connect(ui->UserButton,&QPushButton::clicked,this,&Widget::on_UserButton_clicked);


    server->listen(QHostAddress::Any, 35000);
}

void Widget::slot_clients(int users)
{
    QString str = QString("접속자 수 : %1").arg(users);
    ui->label->setText(str);
}

void Widget::slot_message(QString msg)
{
    ui->textEdit->append(msg);
}

void Widget::on_UserButton_clicked()
{
    UserInfoMgr userMgr;

  // ui->textEdit->append(userMgr);
}



Widget::~Widget()
{
    delete ui;
}

