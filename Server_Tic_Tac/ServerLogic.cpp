#include "ServerLogic.h"

ServerLogic::ServerLogic(QObject *pobj) : QObject (pobj)
{
    objServer = new Server_Tic_Tac;

    arrCommandItem[Message::TEXT] = &ServerLogic::text;
    arrCommandItem[Message::NAME_CLIENTS] = &ServerLogic::nameClients;
    arrCommandItem[Message::CLIENTS] = &ServerLogic::clients;
    arrCommandItem[Message::GAME_INFO] = &ServerLogic::gameInfo;
    arrCommandItem[Message::CONNECTION_INFO] = &ServerLogic::connectionInfo;

    p_timer = new QTimer(this);
    connect(p_timer, SIGNAL(timeout()),
            this,    SLOT(slotUpdate()));
    p_timer->start(1000);

    connect(this, SIGNAL(message(Message)),
            objServer, SLOT(slotSendToClient(Message)));
    connect(objServer, SIGNAL(message(Message)),
            this, SLOT(slotMessage(Message)));
}

//################_______слоты
void ServerLogic::slotMessage(Message msg){
    if(msg.id >= SIZE_COMMAND or msg.id < 0){
        qDebug() << "incorrect client command: " + msg.pSocket->peerName()
                 << QString::number( msg.id);
        return;
    }
    try {
        (this->*arrCommandItem[msg.id])(msg);
    } catch (...) {
    }
}
void ServerLogic::slotUpdate(){
    //qDebug() << "Update info";
    QStringList listPlayers;
    QVector<QVector<qint16> > vField;

    QByteArray bAgameInfo;
    QDataStream outGameInfo(&bAgameInfo, QIODevice::WriteOnly);


    try {


    for(auto it = players.begin(); it != players.end(); it++){

        QByteArray bA;
        QDataStream out(&bA, QIODevice::WriteOnly);
        listPlayers.clear();

        bAgameInfo.clear();
        outGameInfo.device()->seek(0);
        ///формируем список свобоных игроков
        for(auto tmpPlayer : players){
            if(
                   tmpPlayer->playerName != it.value()->playerName and
                   tmpPlayer->pSocket != it.value()->pSocket and
                   !tmpPlayer->playerStatus
               )
            {
                listPlayers << tmpPlayer->playerName;
            }
        }
        //проверяем находится ли игрок в игре
        if(it.value()->playerStatus){
            //прочитать и переслать значение игрового поля
            //отослать чей ход
            //на клиенте заблокировать combobox

            auto &tmpArr = gr[it.value()->roomNumber]->gameField;
            vField.resize(std::end(tmpArr) - std::begin(tmpArr));
            qDebug() << "Размер вектора" << QString::number(vField.size());
            for(auto i = 0; i < vField.size(); i++){
                vField[i].resize(std::end(*tmpArr) - std::begin(*tmpArr));
                qDebug() << "Размер вектора" << QString::number(vField[i].size());
                for(auto j = 0; j < vField.size(); j++){
                    vField[i][j]= tmpArr[i][j];
                }
            }
            outGameInfo << static_cast<qint16>(1) << vField
                        << (QString(gr[it.value()->roomNumber]->statusGame + gr[it.value()->roomNumber]->stepPlayer));


        }
        else{
            //переслать дефолтное значение игрового поля
            //статус никто не подключен
            vField.resize(C_SIZE);
            for(auto it = vField.begin(); it < vField.end(); it++){
                it->resize(C_SIZE);
                for(auto it_1 = it->begin(); it_1 < it->end(); it_1++){
                    *it_1 = 0;
                }
            }
            outGameInfo << static_cast<qint16>(0) << vField
                        << QString("Никто не подключен");
        }





        out << static_cast<quint16>(0) << QTime::currentTime() << static_cast<qint16>(Message::UPDATE)
            << static_cast<qint16>(Message::CONNECTION_INFO) << QString("Подключен к серверу")
            << static_cast<qint16>(Message::CLIENTS) << listPlayers
            << static_cast<qint16>(Message::GAME_INFO) << bAgameInfo;
        emit message(Message(Message::UPDATE, bA, it.value()->pSocket));
    }  
    } catch (...) {
    }
}
void ServerLogic::slotGameOver(qint16 i){
    QString status = gr[i]->statusGame;

    QByteArray readyMsg;
    QDataStream outReady(&readyMsg, QIODevice::WriteOnly);

    //QByteArray bA;
    //QDataStream out(&bA, QIODevice::WriteOnly);

    QVector<QVector <qint16> > vectorField;
    vectorField.reserve(std::end(gr[i]->gameField) - std::begin(gr[i]->gameField));
    for(auto itVec = vectorField.begin(); itVec < vectorField.end(); itVec++){
        itVec->resize(std::end(*(gr[i]->gameField)) - std::begin(*(gr[i]->gameField)));
        for(auto it = itVec->begin(); it < itVec->end(); it++){
            *it = 0;
        }
    }

    outReady << static_cast<quint16>(Message::GAME_INFO) << QTime::currentTime()
             << static_cast<qint16>(2) << vectorField << gr[i]->statusGame;


    emit message(Message(Message::GAME_INFO, readyMsg, gr[i]->socketPlayer0));
    players[gr[i]->socketPlayer0]->playerStatus = false;
    players[gr[i]->socketPlayer0]->roomNumber = -1;

    emit message(Message(Message::GAME_INFO, readyMsg, gr[i]->socketPlayer1));
    players[gr[i]->socketPlayer1]->playerStatus = false;
    players[gr[i]->socketPlayer1]->roomNumber = -1;

    delete gr[i];
    gr[i] = Q_NULLPTR;
}


//_________Реализация интерфейса
void ServerLogic::text(Message& msg){
    QDataStream in(&msg.data, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_3);
    QString str;
    in >> str;
    qDebug() << msg.pSocket->peerName() <<str;
}

void ServerLogic::nameClients(Message &msg){
    QDataStream in(&msg.data, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_3);
    PlayerInfo* plInfo;
    plInfo = new PlayerInfo(players); //возможно косяк с памятью
    in >> plInfo->playerName;
    plInfo->pSocket = msg.pSocket;
    plInfo->playerStatus = false;
    //msg.pSocket->disconnected();
//    connect(msg.pSocket, SIGNAL(disconnected()),
//            plInfo, SLOT(slotDropCell()));
    players[msg.pSocket] = plInfo;
    connect( msg.pSocket, SIGNAL(disconnected()),
             players[msg.pSocket], SLOT(slotDropCell())
            );
    emit message(Message (Message::TEXT, QString("Имя успешно добавленно"), msg.pSocket));
}
void ServerLogic::clients(Message& msg){
    QVector<QString> strList;
    bool _isEmpty = false;
    for(auto it = players.begin(); it != players.end(); it++){
        qDebug() << "поиск по карте";
        if(it.value()->pSocket == msg.pSocket){
            _isEmpty = true;
        }
        else{
            strList.push_back( it.value()->playerName);
            qDebug() << "Добавленное из карты имя " + it.value()->playerName;
        }
    }
    if( _isEmpty ){
        QByteArray bA;
        QDataStream t_out(&bA, QIODevice::WriteOnly);
        t_out << static_cast<quint16>(0)
              << QTime::currentTime()
              << static_cast<qint16>(Message::CLIENTS)
              << strList;
        //qDebug() << "Размер отсылаемого байтМассива " << m.data.size();

        //out << bA;

        //qDebug() << "Размер отсылаемого байтМассива " << m.data.size();


//        qint16 t_size = static_cast<qint16 >( strList.size());
//        out << t_size;
//        qDebug() << t_size;
//        for(auto tmp : strList){
//            QDataStream out(&m.data, QIODevice::WriteOnly);
//            out.setVersion(QDataStream::Qt_5_3);

//            out << tmp;
//        }

        emit message(Message(Message::CLIENTS, bA, msg.pSocket));
        qDebug() << "отправили клиенту список подключенных парней";
    }
    else{
        emit message(Message( Message::TEXT, QString("Сначала добавте Ваше имя"), msg.pSocket));
    }
    //проверить есть ли клиент с таким именем и после этого присалть ему список
    //без его имени
    qDebug() << "Список занчений QStringList";
    for(auto it  = strList.begin(); it < strList.end(); it++){
        qDebug() << "Значение из списка " + *it ;
    }
}

#include<iostream>
void ServerLogic::gameInfo(Message &msg){
    //принять имя второго игрока
    //проверить на наличие свбодной комнаты
    //создать комнату
    //соеденить сигналы окончания игры с сообщением клиету и удаление комнаты
        //в удалении комнату сделать дисконнект
    //если другой номер
    //прочитать данные от игрока и передать в комнату
    QDataStream cin(&msg.data, QIODevice::ReadOnly);
    qint16 item;
    QString tmpStr;
    //читаем что пришло и что с ним делать
    //**********************************************************************************************
    char dCh;
    qint16 dInt;
    std::string dStdStr;
    QString dQStr;
    QString dStrNumb;

    for(qint16 i = 0; i < cin.device()->size(); i++){
        cin >> dInt;
        dStdStr += static_cast<char>(dInt);
        dQStr += static_cast<char>(dInt);
        dStrNumb += QString::number(dInt) + " ";
    }
    qDebug() << "dQStr = " << dQStr
             //<< "dStdStr = " << QString(dStdStr)
             << "dStrNumb = " << dStrNumb;
    std::cout << "dStdStr = " << dStdStr << std::endl;

    //**********************************************************************************************
    cin.device()->seek(0);
    ///********
    cin >> item;
    ///*******************


    //********************
    QTcpSocket* pSocketPl2 = Q_NULLPTR;
    qDebug() << "____" << QString::number(0);
    //создание новой игры
    if(item == 0 and players.contains(msg.pSocket)){
        players[msg.pSocket]->playerStatus = true;
        cin >> tmpStr;
        qDebug() << "____" << QString::number(1);
        for(auto it = players.begin(); it != players.end(); it++){
            qDebug() << "____" << QString::number(1.1);

            if(it.value()->playerName == tmpStr){
                qDebug() << "____" << QString::number(2);
                pSocketPl2 = it.value()->pSocket;
                if(it.value()->playerStatus){
                    emit message(Message(Message::TEXT, QString("Этот игрок занят")));
                    return;
                }
                qDebug() << "____" << QString::number(3);
                it.value()->playerStatus = true;
                break;
            }
        }
        if(!pSocketPl2){
            players[msg.pSocket]->playerStatus = false;
            qDebug() << "Второй игрок не найден c именем " << tmpStr;
            return;
        }
        for(qint16 i = 0; i < ROOMS; i++){
            qDebug() << "____" << QString::number(4);
            if(gr[i] == Q_NULLPTR){
                qDebug() << "____" << QString::number(5);
                QString strPl1, strPl2;
                strPl1 = players[msg.pSocket]->playerName;
                qDebug() << "____" << QString::number(5.1);
                strPl2 = players[pSocketPl2]->playerName;

                qDebug() << "____" << QString::number(5.2);

                gr[i] = new GameRoom( i, strPl1, strPl2);
                qDebug() << "____" << QString::number(6);
                players[msg.pSocket]->roomNumber = i;
                players[pSocketPl2]->roomNumber = i;
                qDebug() << "____" << QString::number(7);
                connect(gr[i], SIGNAL(gameOver(qint16)),
                        this, SLOT(slotGameOver(qint16)));
                return;
            }

        }
        emit message(Message(Message::TEXT, QString("Нет свободных мест на сервере")));
        players[pSocketPl2]->playerStatus = false;
        players[msg.pSocket]->playerStatus = false;
        return;
    }
    //информация по уже существующей игре
    if(item == 1 and players.contains(msg.pSocket)){
        //
        qint16 numRoom = players[msg.pSocket]->roomNumber;
        if(numRoom < 0 and gr[numRoom] == Q_NULLPTR and gr[numRoom]->numberRoom != numRoom){
            qDebug() << "ERROR!!! Такой комнаты " << numRoom << " не существует!";
            return;
        }
        qint16 x,y;
        cin >> x >> y;
        gr[numRoom]->step(players[msg.pSocket]->playerName, x,y);
        return;
    }

    qDebug() << "В gameInfo() что-то пошло не так";
}
void ServerLogic::connectionInfo(Message &){

}
void ServerLogic::update(Message &){

}

