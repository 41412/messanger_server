
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChatServer
TEMPLATE = app

SOURCES += main.cpp\
        widget.cpp \
    chatserver.cpp \
    chatlogin.cpp \
    chatroom.cpp \
    userinfomgr.cpp

HEADERS  += widget.h \
    chatserver.h \
    chatlogin.h \
    chatroom.h \
    chatdata.h \
    userinfomgr.h

FORMS    += widget.ui
