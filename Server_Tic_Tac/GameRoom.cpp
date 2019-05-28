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

}
