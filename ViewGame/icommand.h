#ifndef ICOMMAND_H
#define ICOMMAND_H
#include<QByteArray>

#define SIZE_COMMAND 6

//using commandItem = void (ICommand::*)(const QByteArray&);


class ICommand{
public:
#ifndef MSG_COMMAND
#define MSG_COMMAND
    enum{
        TEXT,
        CLIENTS,
        NAME_CLIENTS,
        GAME_INFO,
        CONNECTION_INFO,
        UPDATE
    };
#endif
    //using commandItem = void (ICommand::*)(const QByteArray&);

public:
    //commandItem arrCommandItem[4];// = {text, nameClients};



public:
    ICommand(){}
public:
    virtual void text(QByteArray&) = 0;
    virtual void nameClients(QByteArray&) = 0;
    virtual void clients(QByteArray&) = 0;
    virtual void gameInfo(QByteArray&) = 0;
    virtual void connectionInfo(QByteArray&) = 0;
    virtual void update(QByteArray&) = 0;
};


#endif // ICOMMAND_H
