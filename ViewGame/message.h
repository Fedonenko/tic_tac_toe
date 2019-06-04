#ifndef MESSAGE_H
#define MESSAGE_H
#include<QByteArray>
#include<QTcpSocket>
#include<QDataStream>
#include<QTime>

struct Message{
#ifndef MSG_COMMAND
#define MSG_COMMAND
    enum{
        TEXT,
        CLIENTS,
        NAME_CLIENTS,
        GAME_INFO,
        CONNECTION_INFO,
        UPDATE
    };
    enum{
        NEW_GAME,
        EXIST_GAME
    };

#endif
    int id;
    QTcpSocket *pSocket;
    QByteArray data;
    Message(QTcpSocket *pS = Q_NULLPTR) :
        pSocket (pS)
    {
        QDataStream out( &data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out << static_cast<qint16>(0) << QTime::currentTime() << id;
    }
    Message(int v, QTcpSocket *pS = Q_NULLPTR) :
        id (v), pSocket (pS)
    {
        QDataStream out( &data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out << static_cast<qint16>(0) << QTime::currentTime() << id;
    }
    Message(int v, QByteArray byteArr, QTcpSocket* pS = Q_NULLPTR) :
        id (v), pSocket (pS), data (byteArr)
    {
//        QDataStream out(&data, QIODevice::WriteOnly);
//        out << static_cast<qint16>(0) << QTime::currentTime() << id;
    }
    Message(int v, QString str, QTcpSocket* pS = Q_NULLPTR):
        id (v), pSocket (pS)
    {
        QDataStream out(&data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out << static_cast<qint16>(0) << QTime::currentTime() << id << str;
    }
};


#endif // MESSAGE_H
