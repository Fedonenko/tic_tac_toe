#ifndef TICTAC_H
#define TICTAC_H

#define N_PORT 2323

#include<QTcpSocket>
#include<QObject>
#include<QDataStream>
#include<QTime>
#include"message.h"



class ClientTicTac : public QObject
{
    Q_OBJECT
private:
    friend class ConnectClass;

    QTcpSocket *p_tcpSocket;
    quint16 nextBlockSize;
public:
    ClientTicTac(QObject* pobj = Q_NULLPTR
                );
    void connectedToServer(const QString&, quint16 );
private:
    void serverCommand(const int n, const QString & str);

  // signals and slots
private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);
    //void slotSendToServer();
    void slotSendToServer(Message);
    //void slotConnect();

signals:
    void infoConnectToServer(const QString&);
    //void tested(const QString&);
    void message(Message);
    //void message(QByteArray);
};

#endif // TICTAC_H
