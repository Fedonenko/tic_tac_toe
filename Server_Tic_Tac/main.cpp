#include <QCoreApplication>
#include"Server_Tic_Tac.h"
#include"ServerLogic.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //Server_Tic_Tac objServer;
    ServerLogic objServerLogic;

    return a.exec();
}
