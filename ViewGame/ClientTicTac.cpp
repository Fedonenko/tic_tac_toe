#include "ClientTicTac.h"

ClientTicTac::ClientTicTac( QObject* pobj) :
    QObject (pobj),
    nextBlockSize (0)
{
    p_tcpSocket = new QTcpSocket(this);
}

void ClientTicTac::connectedToServer(const QString &strHost, quint16 nPort){
    //emit p_tcpSocket->disconnected();
    if(p_tcpSocket->isOpen()){
        p_tcpSocket->disconnectFromHost();
        p_tcpSocket->connectToHost(strHost, nPort);
        return;
    }
    p_tcpSocket->connectToHost(strHost, nPort);
    //connect(p_tcpSocket, SIGNAL(connected()), SLOT(slotConnect()));
    connect(p_tcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(p_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(slotError(QAbstractSocket::SocketError)));

}

void ClientTicTac::slotReadyRead(){
    QDataStream in(p_tcpSocket);
    //p_tcpSocket->bytesToWrite();
    in.setVersion(QDataStream::Qt_5_3);
    for(;;){
        if(!nextBlockSize){
            if(p_tcpSocket->bytesAvailable() < sizeof (quint16)){
                break;
            }
            in >> nextBlockSize;
        }
        if(p_tcpSocket->bytesAvailable() < nextBlockSize){
            break;
        }
        QTime time;
        qint16 cmd;
        in >> time >> cmd;
        emit message( Message(cmd, p_tcpSocket->read(p_tcpSocket->bytesAvailable())));
        nextBlockSize = 0;
    }
}
void ClientTicTac::slotError(QAbstractSocket::SocketError err){
    QString strError =
            "Error " + (err == QAbstractSocket::HostNotFoundError ?
                           "The host was not found." :
                           err == QAbstractSocket::RemoteHostClosedError ?
                               "The remote host is closed." :
                               err == QAbstractSocket::ConnectionRefusedError ?
                                   "The connection was refused." :
                                   QString(p_tcpSocket->errorString())
                                   );
    //куда то отправить ошибку
    QByteArray bA;
    QDataStream out(&bA, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);
    out << strError;
    emit message(Message( Message::CONNECTION_INFO,bA));
}
//void ClientTicTac::slotSendToServer(){
//    QByteArray arrBlock;
//    QDataStream out(&arrBlock, QIODevice::WriteOnly);

//    QString str;

//    out.setVersion(QDataStream::Qt_5_3);
//    out << static_cast<quint16>(0) << QTime::currentTime() << str;

//    out.device()->seek(0);
//    out << static_cast<quint16>(arrBlock.size() - sizeof (quint16));

//    p_tcpSocket->write(arrBlock); //отправили
//}
void ClientTicTac::slotSendToServer(Message msg){
    //QByteArray arrBlock;
    QDataStream out(&msg.data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);

    //out << static_cast<quint16>(0) << QTime::currentTime() << msg.id;

    out.device()->seek(0);
    out << static_cast<quint16>(msg.data.size() - sizeof (quint16))
        << QTime::currentTime() << msg.id;

    p_tcpSocket->write(msg.data);
    p_tcpSocket->flush();
    qDebug() << "отправленно " + QString::number(msg.id);
}
