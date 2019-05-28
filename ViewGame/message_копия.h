#ifndef MESSAGE_H
#define MESSAGE_H
#include<QByteArray>

struct Message{
    Message(int v, QByteArray byteArr) :
        id (v), data (byteArr)
    {}
    int id;
    QByteArray data;
};


#endif // MESSAGE_H
