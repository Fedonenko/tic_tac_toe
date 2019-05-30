#ifndef ICOMMAND_H
#define ICOMMAND_H
#include<QByteArray>
#include"message.h"

#define SIZE_COMMAND 6

//using commandItem = void (ICommand::*)(const QByteArray&);


class ICommand{
public:


    //using commandItem = void (ICommand::*)(const QByteArray&);

public:
    //commandItem arrCommandItem[4];// = {text, nameClients};



public:
    ICommand(){}
public:
    virtual void text(Message&) = 0;
    virtual void nameClients(Message&) = 0;
    virtual void clients(Message&) = 0;
    virtual void gameInfo(Message&) = 0;
    virtual void connectionInfo(Message&) = 0;
    virtual void update(Message&) = 0;
};


#endif // ICOMMAND_H
