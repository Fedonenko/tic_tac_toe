#include "GameRoom.h"

GameRoom::GameRoom(qint16 number,
                   QString p0, QString p1,
                   QTcpSocket* pl0,
                   QTcpSocket* pl1
                   ) :
    socketPlayer0(pl0),
    socketPlayer1(pl1) ,
  player0 (p0), player1 (p1),
  numberRoom(number)
{
    qDebug() << "___GameRoom____" << QString::number(0);
    if( QTime::currentTime().msec()%2 ){
        stepPlayer = player0;
    }
    else{
        stepPlayer = player1;
    }
    qDebug() << "___GameRoom____" << QString::number(1);
    statusGame = "Ход игрока ";

}
bool GameRoom::win(qint16 v,qint16 (&a)[C_SIZE][C_SIZE]){
    bool
            glD = true,
            pobD = true,
            row = true,
            column = true;
    qint16 n = std::end(a) - std::begin(a);
    qint16 m = std::end(*a) - std::begin(*a);
    for(qint16 i = 0; i < n ; i++){
        pobD = pobD && (a[i][n-i-1] == v)? true: false;
        row = true;
        column = true;
        for(qint16 j = 0; j < m; j++){
            if(i == j){
                glD = glD && (a[i][j] == v)? true: false;
            }
            if(row){
                row = row && (a[i][j] == v)? true: false;
            }
            if(column){
                column = column &&(a[j][i] == v)? true: false;
            }
        }
        if(row)
            return row;
        if(column)
            return  column;
    }

    return glD || pobD;
}
void GameRoom::step(QString nameStep, qint16 i, qint16 j){
    qDebug() << "____step in GameRoom";
    if(nameStep != stepPlayer){
        //ход не того игрока
        return;
    }
    qDebug() << "____step in GameRoom____0.0";
    if(gameField[i][j]){
        //уже занятая ячейка поля
        return;
    }
    qDebug() << "____step in GameRoom____0";
    gameField[i][j] = (player0 == nameStep)? 1: -1;
    qDebug() << "_____ячейка поля = " << QString::number(gameField[i][j]);
    if (win(gameField[i][j], gameField)){
        //конец игры
        statusGame = "Выиграл " + stepPlayer;
        emit gameOver(numberRoom);
        return;
    }
    else{
        qDebug() << "____step in GameRoom____1";
        //меняем ход
        stepPlayer = (stepPlayer == player1)? player0: player1;
        //проверить на ничью
        for(auto itAr = std::begin( gameField); itAr < std::end(gameField); itAr++ ){
            for(auto it = std::begin(*itAr); it < std::end(*itAr); it++){
                if(*it == 0)
                    return;
            }
        }
        //ничья
        statusGame = "Ничья ";
        qDebug() << "____step in GameRoom____2";

        emit gameOver(numberRoom);
    }
}
