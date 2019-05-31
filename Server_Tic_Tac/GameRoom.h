#ifndef GAMEROOM_H
#define GAMEROOM_H

#include<QObject>
#include<QString>
#include<QTime>
#include<QVector>
#include<QTcpSocket>


#define C_SIZE 3

class GameRoom : public QObject
{
    Q_OBJECT
public:
    QString player0;
    QTcpSocket* socketPlayer0;

    QString player1;
    QTcpSocket* socketPlayer1;

    QString stepPlayer;
    QString statusGame;
    int gameField[C_SIZE][C_SIZE] {{0}};
    int numberRoom;
    //QVector<int > v1;
    //QVector<QVector<int> > v;


public:
    GameRoom( int,
              const QString&p0, const QString&p1,
              QTcpSocket* pl0 = Q_NULLPTR,
              QTcpSocket* pl1 = Q_NULLPTR
            );
public:
    ///
    void step(QString, int , int);
    ///проверка матрицы выигрышная или нет
    bool win(int v,int (&a)[C_SIZE][C_SIZE]);

signals:
    void gameOver(int);


};

#endif // GAMEROOM_H
