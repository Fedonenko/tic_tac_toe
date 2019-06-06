#ifndef MESSAGE_H
#define MESSAGE_H
#include<QByteArray>
#include<QTcpSocket>
#include<QDataStream>
#include<QTime>



struct Message{
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

    Message(QTcpSocket *pS = Q_NULLPTR) :
        pSocket (pS)
    {
        QDataStream out( &data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out << static_cast<quint16>(0) << QTime::currentTime() << id;
    }
    Message(qint16 v, QTcpSocket *pS = Q_NULLPTR) :
        id (v), pSocket (pS)
    {
        QDataStream out( &data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out << static_cast<quint16>(0) << QTime::currentTime() << id;
    }
    Message(qint16 v, QByteArray byteArr, QTcpSocket *pS = Q_NULLPTR) :
        id (v), data (byteArr), pSocket (pS)
    {
//        QDataStream out(&data, QIODevice::WriteOnly);
//        out << static_cast<quint16>(0) << QTime::currentTime() << id;
    }
    Message(qint16 v, QString str, QTcpSocket* pS = Q_NULLPTR):
        id (v), pSocket (pS)
    {
        QDataStream out(&data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_3);
        out << static_cast<quint16>(0) << QTime::currentTime() << id << str;
    }
    qint16 id;
    QTcpSocket *pSocket;
    QByteArray data;
};


#endif // MESSAGE_H
