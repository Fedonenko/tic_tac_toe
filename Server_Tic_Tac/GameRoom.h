#ifndef GAMEROOM_H
#define GAMEROOM_H

#include<QString>
#include<QTime>
#include<QVector>


#define C_SIZE 3

class GameRoom
{
public:
    QString player0;
    QString player1;
    QString stepPlayer;
    QString statusGame;
    int gameField[C_SIZE][C_SIZE] {{0}};
    //QVector<int > v1;
    //QVector<QVector<int> > v;


public:
    GameRoom(const QString&p0, const QString&p1);
public:
    ///
    void step(QString, int , int);
    ///проверка матрицы выигрышная или нет
    bool win(int v,int (&a)[C_SIZE][C_SIZE]);


};

#endif // GAMEROOM_H
