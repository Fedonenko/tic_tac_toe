#include "ConnectClass.h"

ConnectClass::ConnectClass(QObject *pobj) : ICommand (), QObject(pobj)
{
    objClient = new ClientTicTac;
    objView = new MyView;

    arrCommandItem[Message::TEXT] = &ConnectClass::text;
    arrCommandItem[Message::CLIENTS] = &ConnectClass::clients;
    arrCommandItem[Message::NAME_CLIENTS] = &ConnectClass::nameClients;
    arrCommandItem[Message::GAME_INFO] = &ConnectClass::gameInfo;
    arrCommandItem[Message::CONNECTION_INFO] = &ConnectClass::connectionInfo;
    arrCommandItem[Message::UPDATE] = &ConnectClass::update;

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
    connect(objView->p_listPlayers, SIGNAL(activated(const QString&)),
            this,       SLOT(slotSendNamePlayer2(const QString&)));

    connect(objView->p_brc, SIGNAL(butClick(My_XY)),
            this,    SLOT(slotButClick(My_XY) ));

    objView->show();

}

//_________________СЛОТЫ
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
void ConnectClass::slotSendNamePlayer2(const QString& name){
    qDebug() << name;
    QByteArray bA;
    QDataStream out(&bA, QIODevice::WriteOnly);

    out << static_cast<quint16>(0) << QTime::currentTime() << static_cast<qint16>(Message::GAME_INFO)
        << static_cast<qint16>(Message::NEW_GAME) << name;

    //__________debug
    QDataStream debIn(&bA,QIODevice::ReadOnly);
    quint16 dsize;
    qint16 dcmd0, dcmd1;
    QTime dtime;
    QString dname;
    debIn >> dsize >> dtime >> dcmd0 >> dcmd1 >> dname;
    qDebug() << dsize << dtime << dcmd0 << dcmd1 << dname;

    emit message(Message(Message::GAME_INFO, bA));
    //__________debug
    //QDataStream debIn(&bA,QIODevice::ReadOnly);
    //int dsize, dcmd0, dcmd1;
    //QTime dtime;
    //QString dname;
    debIn.device()->seek(0);
    debIn >> dsize >> dtime >> dcmd0 >> dcmd1 >> dname;
    qDebug() << dsize << dtime << dcmd0 << dcmd1 << dname;
}

//
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
void ConnectClass::slotButClick(My_XY inf){
    QByteArray bA;
    QDataStream out(&bA, QIODevice::WriteOnly);
    out << static_cast<quint16>(0) << QTime::currentTime() << static_cast<qint16>(Message::GAME_INFO)
        << static_cast<qint16>(Message::EXIST_GAME)
        << static_cast<qint16>(inf.x) << static_cast<qint16>(inf.y);
    emit message(Message(Message::GAME_INFO, bA));
    //______________________debug
    qDebug() << "Значение Х = " << QString::number(inf.x)
             << "Значение Y = " << QString::number(inf.y);
    QDataStream in(&bA, QIODevice::ReadOnly);
    quint16 dsize;
    qint16 dcmd0,dcmd1, dx, dy;
    QTime dtime;
    in >> dsize >> dtime >> dcmd0 >> dcmd1 >> dx >> dy;
    qDebug() << dsize << dtime << dcmd0 << dcmd1 << dx << dy;
    //______________________debug_end
}

//___________Реализация Интерфейса
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
    in >> strList;
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

    qint16 idCommand;
    QVector<QVector<qint16>> vField;
    QString strStatus;
    in >> idCommand >> vField >> strStatus;
    qDebug() << "------gameInfo------";
    objView->setField(vField);
    objView->p_gameState->setText(strStatus);


}
void ConnectClass::connectionInfo(QByteArray& bA){
    QDataStream in(&bA, QIODevice::ReadOnly);
    QString str;
    in >> str;
    objView->p_serverConnection->setText(str);
}
void ConnectClass::update(QByteArray& bA){
    QStringList listPlayers;
    qint16 idCommand;
    QString str;

    QDataStream in(&bA, QIODevice::ReadOnly);
    in >> idCommand >> str;
    objView->p_serverConnection->setText(str);

    in >> idCommand >> listPlayers;
    objView->p_listPlayers->clear();
    objView->p_listPlayers->addItems(listPlayers);

    QByteArray msgBA;
    in >> idCommand >> msgBA;

    qDebug() << "___Update info___" << QString::number(idCommand);


    (this->*arrCommandItem[idCommand])(msgBA);



    qDebug() << "Update info";

}
