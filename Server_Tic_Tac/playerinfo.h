#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include<QObject>
#include<QString>
#include<QTcpSocket>

class PlayerInfo : public QObject
{
public:
    QString playerName;
    //QString peerName;
    QTcpSocket* pSocket;

    bool playerStatus;

    QMap<QTcpSocket*, PlayerInfo*> &mapPlayers;

    PlayerInfo( QMap<QTcpSocket*, PlayerInfo*> &v, QObject *pobj = Q_NULLPTR) :
        QObject(pobj),
        mapPlayers (v)
    {

    }
public slots:
    void slotDropCell(){

    }
};

#endif // PLAYERINFO_H
