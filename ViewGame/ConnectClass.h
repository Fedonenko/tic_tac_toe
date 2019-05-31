#ifndef CONNECTCLASS_H
#define CONNECTCLASS_H

#include<myview.h>
#include<ClientTicTac.h>
#include"message.h"
#include"icommand.h"


class ConnectClass : public QObject,
        virtual public ICommand
{
    Q_OBJECT
private:
    using commandItem = void (ConnectClass::*)(QByteArray&);
    commandItem arrCommandItem[SIZE_COMMAND];
    ClientTicTac *objClient;
    MyView *objView;
public:
    ConnectClass(QObject *pobj = Q_NULLPTR);

    //void performOperation();
    ///сообщение с текстом
    virtual void text(QByteArray &);
    ///сообщение с именем клинета
    virtual void nameClients(QByteArray&);
    ///сообщение с списком подключенных коиентов
    virtual void clients(QByteArray&);
    ///игровая информация
    virtual void gameInfo(QByteArray &);
    ///информация о соединении
    virtual void connectionInfo(QByteArray &);
    ///
    virtual void update(QByteArray &);
// signals and slots
private slots:
    //void slotInfoConnectToServer(const QString&);
    ///перерподключение к заданному серверу
    void slotReconnectedToServer();
    ///отсылает имя игрока и запрашивает подключенных
    void slotSendName();
    ///отправляет выбранное имя второг игрока
    void slotSendNamePlayer2(const QString &);
    ///принимает сообщения от клинета
    void slotMessage(Message);
signals:
    ///отсылает сообщения клиенту
    void message(Message);
};

#endif // CONNECTCLASS_H
