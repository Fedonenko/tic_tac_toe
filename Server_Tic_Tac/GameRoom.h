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
    qint16 gameField[C_SIZE][C_SIZE] {{0}};
    qint16 numberRoom;
    //QVector<int > v1;
    //QVector<QVector<int> > v;


public:
    GameRoom( qint16,
              QString p0, QString p1,
              QTcpSocket* pl0 = Q_NULLPTR,
              QTcpSocket* pl1 = Q_NULLPTR
            );
public:
    ///
    void step(QString, qint16, qint16);
    ///проверка матрицы выигрышная или нет
    bool win(qint16 v,qint16 (&a)[C_SIZE][C_SIZE]);

signals:
    void gameOver(qint16);


};

#endif // GAMEROOM_H
