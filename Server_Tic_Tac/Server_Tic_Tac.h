#ifndef SERVER_TIC_TAC_H
#define SERVER_TIC_TAC_H

#define N_PORT 2323

#include<QObject>
#include<QTcpServer>
#include<QTcpSocket>
#include<QDataStream>
#include<QTime>
#include<QException>
#include<QDebug>
#include"message.h"


//enum {
//    TEXT,
//    CLIENTS,
//    CLIENTS_NAME,
//    GAME_INFO
//};

class Server_Tic_Tac : public QObject//, virtual public
{
    Q_OBJECT
private:
    QTcpServer *p_tcpServer;
    quint16 nextBlockSize;

private:
    void sendToClient(QTcpSocket *pSocket,const qint16 cmd,const QString& str);
    bool sendToClient(const QString &name, const qint16 cmd, const QString& str);
public:
    Server_Tic_Tac(quint16 nPort = N_PORT, QObject* pobj = Q_NULLPTR);
public slots:
    virtual void slotNewConnection();
    void slotReadClient();
    void slotSendToClient(Message);
signals:
    void message(Message);

};

#endif // SERVER_TIC_TAC_H
