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

void Widget::slot_UserButton()
{
    UserInfoMgr userMgr;

    ui->textEdit->append("모든 유저 닉네임");

    userMgr.totalUser();


}



Widget::~Widget()
{
    delete ui;
}

