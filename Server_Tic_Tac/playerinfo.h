#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include<QObject>
#include<QString>
#include<QTcpSocket>

class PlayerInfo : public QObject
{
public:
    QString playerName;
    ///сокет подключенного игрока
    QTcpSocket* pSocket;
    ///статус игрока
    bool playerStatus;
    ///номер игровой комнаты в которой находится игрок
    qint16 roomNumber = -1;
    ///ссылка на карту с информацией о подключенных игроках
    QMap<QTcpSocket*, PlayerInfo*> &mapPlayers;


public:
    PlayerInfo( QMap<QTcpSocket*, PlayerInfo*> &v, QObject *pobj = Q_NULLPTR) :
        QObject(pobj),
        mapPlayers (v)
    {

    }
public slots:
    ///Удалить ячейку с данными о пользователе при отключении пользователя
    void slotDropCell(){
        
    }
};

#endif // PLAYERINFO_H
