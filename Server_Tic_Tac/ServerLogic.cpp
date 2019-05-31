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
    QVector<QVector<int> > vField;

    QByteArray bAgameInfo;
    QDataStream outGameInfo(&bAgameInfo, QIODevice::WriteOnly);


    try {


    for(auto it = players.begin(); it != players.end(); it++){

        QByteArray bA;
        QDataStream out(&bA, QIODevice::WriteOnly);
        listPlayers.clear();

        bAgameInfo.clear();
        outGameInfo.device()->seek(0);

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
        if(it.value()->playerStatus){
            //прочитать и переслать значение игрового поля
            //отослать чей ход
            //на клиенте заблокировать combobox

            auto &tmpArr = gr[it.value()->roomNumber]->gameField;
            vField.resize(std::end(tmpArr) - std::begin(tmpArr));
            for(auto i = 0; i < vField.size(); i++){
                vField[i].resize(std::end(*tmpArr) - std::begin(*tmpArr));
                for(auto j = 0; j < vField.size(); j++){
                    vField[i][j]= tmpArr[i][j];
                }
            }
            outGameInfo << static_cast<qint16>(1) << vField
                        << gr[it.value()->roomNumber]->statusGame + gr[it.value()->roomNumber]->stepPlayer ;


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





        out << static_cast<qint16>(0) << QTime::currentTime() << Message::UPDATE
            << Message::CONNECTION_INFO << QString("Подключен к серверу")
            << Message::CLIENTS << listPlayers
            << Message::GAME_INFO << bAgameInfo;
        emit message(Message(Message::UPDATE, bA, it.value()->pSocket));
    }  
    } catch (...) {
    }
}
void ServerLogic::slotGameOver(int i){
    QString status = gr[i]->statusGame;

    QByteArray readyMsg;
    QDataStream outReady(&readyMsg, QIODevice::WriteOnly);

    //QByteArray bA;
    //QDataStream out(&bA, QIODevice::WriteOnly);

    QVector<QVector <int> > vectorField;
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
//void ServerLogic::nameClients(Message& msg){
//    QDataStream in(&msg.data, QIODevice::ReadOnly);
//    in.setVersion(QDataStream::Qt_5_3);
//    PlayerInfo plInfo;
//    in >> plInfo.playerName;
//    if( players.contains(plInfo.playerName) ){
//        Message tmpM(Message::TEXT, QString("Игрок с таким именем уже существует"), msg.pSocket);
//        emit ServerLogic::message(tmpM);
//        return;
//    }
//    else{
//        plInfo.peerName = msg.pSocket->peerName();
//        plInfo.pSocket = msg.pSocket;
//        plInfo.playerStatus = false;

//        players[plInfo.playerName] = plInfo;
//        qDebug() << "Добавленное имя в карту " + (players[plInfo.playerName]).playerName +
//                " с именем пира " + plInfo.peerName + msg.pSocket->peerName();
//        //qDebug() <<
//        emit message(Message (Message::TEXT, QString("Имя успешно добавленно"), msg.pSocket));
//    }

//}
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
              << Message::CLIENTS
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
    cin >> item;
    QTcpSocket* pSocketPl2;
    //создание новой игры
    if(item == 0 and players.contains(msg.pSocket)){
        players[msg.pSocket]->playerStatus = true;
        cin >> tmpStr;
        for(auto it = players.begin(); it != players.end(); it++){
            if(it.value()->playerName == tmpStr){
                pSocketPl2 = it.value()->pSocket;
                if(it.value()->playerStatus){
                    emit message(Message(Message::TEXT, QString("Этот игрок занят")));
                    return;
                }
                it.value()->playerStatus = true;
                break;
            }
        }
        for(int i = 0; i < ROOMS; i++){
            if(gr[i] == Q_NULLPTR){

                gr[i] = new GameRoom( i,players[msg.pSocket]->playerName, players[pSocketPl2]->playerName);
                players[msg.pSocket]->roomNumber = i;
                players[pSocketPl2]->roomNumber = i;
                connect(gr[i], SIGNAL(gameOver(int)),
                        this, SLOT(slotGameOver(int)));
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
        int numRoom = players[msg.pSocket]->roomNumber;
        if(gr[numRoom] == Q_NULLPTR and gr[numRoom]->numberRoom != numRoom){
            qDebug() << "ERROR!!! Такой комнаты " << numRoom << " не существует!";
            return;
        }
        int x,y;
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

