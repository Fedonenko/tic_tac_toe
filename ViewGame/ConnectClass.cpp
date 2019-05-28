#include "ConnectClass.h"

ConnectClass::ConnectClass(QObject *pobj) : QObject(pobj), ICommand ()
{
    objClient = new ClientTicTac;
    objView = new MyView;

    arrCommandItem[Message::TEXT] = &ConnectClass::text;
    arrCommandItem[Message::CLIENTS] = &ConnectClass::clients;
    arrCommandItem[Message::NAME_CLIENTS] = &ConnectClass::nameClients;
    arrCommandItem[Message::GAME_INFO] = &ConnectClass::gameInfo;
    arrCommandItem[Message::CONNECTION_INFO] = &ConnectClass::connectionInfo;

    connect(objView->p_buttonConnect, SIGNAL(clicked()),
            this,   SLOT(slotReconnectedToServer()));
//    connect(objClient->p_tcpSocket, SIGNAL(connected()),
//            this,   SLOT(slotIsConnect())
//                );
    connect(objView->p_buttonNamePlayer, SIGNAL(clicked()),
                        SLOT(slotSendName()));

    connect(this, SIGNAL(message(Message)),
            objClient, SLOT(slotSendToServer(Message)));

    connect(objClient, SIGNAL(message(Message)),
            this,   SLOT(slotMessage(Message)));

    objView->show();

}

void ConnectClass::slotReconnectedToServer(){
    //QString str = objView->p_fieldServersIp->text();
    objClient->connectedToServer(
                objView->p_fieldServersIp->text(),
                N_PORT);
}
void ConnectClass::slotSendName(){
    QString str = objView->p_editNamePlayers->text();
    if(objClient->p_tcpSocket->isOpen()){
        emit message(Message(Message::NAME_CLIENTS, str));
        emit message(Message(Message::CLIENTS, QString("Запрос списка клиентов")));
    }
}

//отправить имя игрока при подключении к серверу и список подключенных игроков
//void ConnectClass::slotIsConnect(){
//    if(objView->p_editNamePlayers->text() != ""){
//        //emit message(Message(Message::TEXT, QString("какой то текст")));

//        emit message(Message(Message::NAME_CLIENTS, objView->p_editNamePlayers->text()));
//        qDebug() << "отправлен сигнал с именем";
//        //for(int i = 0; i < 1000000; i++){ QString str = "  "; }
//        emit message(Message(Message::CLIENTS, QString("Запрос списка клиентов")));
//        qDebug() << "отправлен сигнал с запросом на отправку списка клиентов";
//        //for(int i = 0; i < 1000000; i++){ QString str = "  "; }
//        //emit message(Message(Message::TEXT, QString(" Someting text")));

//    }
//}

void ConnectClass::slotMessage(Message msg){
    qDebug() << " <<<Номер команды сообщения: "
             << QString::number(msg.id);
    if(msg.id >= SIZE_COMMAND or msg.id < 0){
        objView->p_textInfo->setText(
                    "incorrect server command: " +
                    QString::number( msg.id));
        return;
    }
    try {
        (this->*arrCommandItem[msg.id])(msg.data);
    } catch (...) {
    }
}

//void performOperation

void ConnectClass::text( QByteArray &bA){
    QDataStream in(&bA, QIODevice::ReadOnly);
    QString str;
    in >> str;
    objView->p_textInfo->setText(str);
}
void ConnectClass::nameClients(QByteArray& bA){
    QDataStream in(&bA, QIODevice::ReadOnly);
    QString str;

}
void ConnectClass::clients(QByteArray& bA){
    QDataStream in(&bA, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_3);
    QVector<QString> strList;

//    QByteArray t_bA;
//    QDataStream out(&t_bA, QIODevice::WriteOnly);
//    out << bA;

//    QDataStream t_in(&t_bA, QIODevice::ReadOnly);
//    t_in >> strList;

    in >> strList;

//    qint16 t_size;
//    in >> t_size;
//    qDebug() << t_size;
//    QString t_str;
    for(auto it = strList.begin(); it < strList.end(); it++){
        objView->p_listPlayers->addItem(*it);
        qDebug() << *it;
    }

    qDebug() << "Пришёл Сигнал со списком клинетов";
    if(strList.isEmpty()){
        qDebug() << "Список пуст";
    }
    for(auto it = strList.begin(); it < strList.end(); it++){
        qDebug() << QString(*it);
    }
}
void ConnectClass::gameInfo(QByteArray& bA){
    QDataStream in(&bA, QIODevice::ReadOnly);
    QString str;

}
void ConnectClass::connectionInfo(QByteArray& bA){
    QDataStream in(&bA, QIODevice::ReadOnly);
    QString str;
    in >> str;
    objView->p_serverConnection->setText(str);
}
