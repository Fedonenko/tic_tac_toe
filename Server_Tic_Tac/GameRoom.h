#ifndef GAMEROOM_H
#define GAMEROOM_H

#include<QString>
#include<QTime>

#define C_SIZE 3

class GameRoom
{
public:
    QString player0;
    QString player1;
    QString stepPlayer;
    int gameField[C_SIZE][C_SIZE] {{0}};

public:
    GameRoom(const QString&p0, const QString&p1);
public:

};

#endif // GAMEROOM_H
