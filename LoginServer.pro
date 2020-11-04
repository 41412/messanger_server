
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChatServer
TEMPLATE = app

SOURCES += main.cpp\
    basesessionproxy.cpp \
    chatdataprotocol.cpp \
    chatfriendmgr.cpp \
    chatloginmgr.cpp \
    chatroommgr.cpp \
    chatsessiondata.cpp \
    chatsessionproxy.cpp \
    chatsocketmgr.cpp \
    chattransmit.cpp \
    chatuserdata.cpp \
    chatuserdatamgr.cpp \
        widget.cpp \
    chatserver.cpp \
    userinfomgr.cpp \
    chatroom.cpp

HEADERS  += widget.h \
    basesessionproxy.h \
    chatdataprotocol.h \
    chatfriendmgr.h \
    chatloginmgr.h \
    chatroommgr.h \
    chatserver.h \
    chatdata.h \
    chatsessiondata.h \
    chatsessionproxy.h \
    chatsocketmgr.h \
    chattransmit.h \
    chatuserdata.h \
    chatuserdatamgr.h \
    userinfomgr.h \
    chatroom.h

FORMS    += widget.ui
