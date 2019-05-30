#include "GameRoom.h"

GameRoom::GameRoom(const QString &p0, const QString &p1) :
    player0 (p0), player1 (p1)
{
    if( QTime::currentTime().msec()%2 ){
        stepPlayer = player0;
    }
    else{
        stepPlayer = player1;
    }
    statusGame = "Ход игрока ";

//    for(auto itAr = std::begin( gameField); itAr < std::end(gameField); itAr++ ){
//        for(auto it = std::begin(*itAr); it < std::end(*itAr); it++){

//        }
//    }

}
bool GameRoom::win(int v,int (&a)[C_SIZE][C_SIZE]){
    bool
            glD = true,
            pobD = true,
            row = true,
            column = true;
    int n = std::end(a) - std::begin(a);
    int m = std::end(*a) - std::begin(*a);
    for(int i = 0; i < n ; i++){
        pobD = pobD && (a[i][n-i-1] == v)? true: false;
        row = true;
        column = true;
        for(int j = 0; j < m; j++){
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
void GameRoom::step(QString nameStep, int i, int j){
    if(nameStep != stepPlayer){
        return;
    }
    if(gameField[i][j]){
        return;
    }
    gameField[i][j] = (player0 == nameStep)? 1: -1;
    if (win(gameField[i][j], gameField)){
        //конец игры
    }
    else{
        //меняем ход
        stepPlayer = (stepPlayer == player1)? player0: player1;
        //проверить на ничью
        for(auto itAr = std::begin( gameField); itAr < std::end(gameField); itAr++ ){
            for(auto it = std::begin(*itAr); it < std::end(*itAr); it++){
                if(gameField[i][j] == 0)
                    return;
            }
        }
        //ничья
        statusGame = "Ничья ";
    }
}
