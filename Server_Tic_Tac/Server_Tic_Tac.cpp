#include "Server_Tic_Tac.h"

Server_Tic_Tac::Server_Tic_Tac(quint16 nPort, QObject* pobj) :
    QObject(pobj),
    nextBlockSize (0)
{
    p_tcpServer = new QTcpServer(this);
    if(!p_tcpServer->listen(QHostAddress::Any, nPort)){
        qDebug() << "Server Error\n Unable to start the server: " + p_tcpServer->errorString();
        p_tcpServer->close();
        return;
    }
    connect(p_tcpServer, SIGNAL(newConnection()),
            this, SLOT(slotNewConnection()));

    qInfo() << QString("конец");

}

void Server_Tic_Tac::slotNewConnection(){
    QTcpSocket *pClientSocket = p_tcpServer->nextPendingConnection();
    connect(pClientSocket, SIGNAL(disconnected()),
            pClientSocket, SLOT(deleteLater()));
    connect(pClientSocket, SIGNAL(readyRead()),
            this, SLOT(slotReadClient()));
    //qDebug("slotNewConnection");
    //pClientSocket->peerName();
    //emit message(Message(2,QByteArray(),pClientSocket));

//    QByteArray bA;
//    QDataStream out(&bA, QIODevice::WriteOnly);
//    out << static_cast<qint16>(0)<< QTime::currentTime() << static_cast<int>(0)
//        << QString("Подключен к серверу");
    //sendToClient(pClientSocket, 4, QString("Подключен к серверу"));
    slotSendToClient(
                Message(Message::CONNECTION_INFO, QString("Подключение успешно"), pClientSocket)
                );

    //##################################################
    //добавить в карту данные о новом клиенте
}

void Server_Tic_Tac::slotReadClient(){
    QTcpSocket *pClientSocket = static_cast<QTcpSocket*>(sender());
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_5_3);
    qDebug("slotreadClient");
    quint16 nextBlockSize = 0;
    for(;;){
        if(!nextBlockSize){
            if(pClientSocket->bytesAvailable() < sizeof(quint16)){
                break;
            }
            in >> nextBlockSize;
        }
        if(pClientSocket->bytesAvailable() < nextBlockSize){
            break;
        }
        QTime time;
        int cmd;
        //QString str;
        in >> time >> cmd;
        qDebug() << "Принято сообщение: " << QString::number(cmd);
        emit message(
                    Message(
                        cmd,
                        pClientSocket->read(pClientSocket->bytesAvailable()),
                        pClientSocket)
                    );

        QString strTmp = pClientSocket->peerAddress().toString() + ':' +
                QString::number( pClientSocket->peerPort() );

        qDebug() << "Переданно сообщение " << QString::number(cmd);
//                 //<< QString::number( pClientSocket->peerAddress().toIPv4Address()) // хрень
//                 << pClientSocket->peerName() << pClientSocket->peerPort();
//        qDebug() << pClientSocket->localAddress()
//                 << " Адрес туСтринг: " << pClientSocket->peerAddress().toString();
//        qDebug() << "Так будет выглядеть адрес строкой: " << strTmp;

        nextBlockSize = 0;
        //################################################
        //что то сделать с присланным от клиента сообщением
    }
}

//void Server_Tic_Tac::sendToClient(QTcpSocket *pSocket, const int cmd, const QString &str){
//    QByteArray arrBlock;
//    QDataStream out(&arrBlock, QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_5_3);

//    out << static_cast<quint16>(0) << QTime::currentTime() << cmd << str;
//    out.device()->seek(0);

//    out << static_cast<quint16>(arrBlock.size() - sizeof(quint16));

//    //qDebug("sendToClient");
//    pSocket->write(arrBlock);
//    qDebug() << "Send of clients: " + pSocket->peerName();
//}

//bool Server_Tic_Tac::sendToClient(const QString&, const int, const QString&){

//    return true;
//}
void Server_Tic_Tac::slotSendToClient(Message msg){
    //QByteArray arrBlock;
    QDataStream out(&msg.data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);

    //out << static_cast<quint16>(0) << QTime::currentTime() << msg.id;
    //out << QTime::currentTime() << msg.id;
    out.device()->seek(0);

    out << static_cast<quint16>(msg.data.size() - sizeof(quint16))
        << QTime::currentTime() << msg.id;

    //qDebug("sendToClient");
    msg.pSocket->write(msg.data);
    msg.pSocket->flush();//кастыль, нужно подумать как убрать
    qDebug() << "отправленно " + QString::number(msg.id);
}
