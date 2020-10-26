#ifndef DATAENUM_H
#define DATAENUM_H

#include "chatserver.h"

//define Data
#define SERVER_PORT 35000

#define SUCCESS 0
#define FAIL 1

typedef struct _userinfo
{
    QString nickName;
    QString passWord;
}userinfo;



#endif // DATAENUM_H
