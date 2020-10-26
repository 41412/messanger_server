#include <QApplication>
#include "widget.h"
#include "userinfomgr.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("로그인 서버");
    w.show();

    w.show();


    return a.exec();
}
