#ifndef SERVERLOGIC_H
#define SERVERLOGIC_H

#include"Server_Tic_Tac.h"
#include"icommand.h"
#include"playerinfo.h"
#include"message.h"
#include"GameRoom.h"
#include<QTimer>
#include<QException>

#define ROOMS 15// дефолтное число под  ключения 30, по 2 игрока в каждой комнате

class ServerLogic :
        public QObject, virtual public ICommand
{
    Q_OBJECT
private:
    using commandItem = void (ServerLogic::*)(Message&);

    commandItem arrCommandItem[SIZE_COMMAND];//массив делегат
    QMap<QTcpSocket*, PlayerInfo*> players; //список подключенных игроков и инфо о них
    Server_Tic_Tac* objServer;
    GameRoom* gr[ROOMS]{Q_NULLPTR};//массив игровых комнат, ограниченое число для ограничения максимальной нагрузки
    QTimer *p_timer;


public:
    ServerLogic(QObject *pobj = Q_NULLPTR);
private:
    ///текст
    virtual void text(Message&);
    ///внести данные о клиенте к карту
    virtual void nameClients(Message&);
    ///запрос списка подключенных клиентов клиентов
    virtual void clients(Message&);
    ///клиент прислал информацию о игре и ждёт ответа
    virtual void gameInfo(Message&);
    ///
    virtual void connectionInfo(Message&);
    ///
    virtual void update(Message&);
private slots:
    void slotMessage(Message);
    void slotUpdate();
    void slotGameOver(qint16);
signals:
    void message(Message);
};

#endif // SERVERLOGIC_H
