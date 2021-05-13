#ifndef SERVERAGENT_H
#define SERVERAGENT_H

#include"netserver.h"
#include<chrono>
#include<thread>
#include<QPushButton>
class serveragent:public netserver{
    Q_OBJECT
    protected:

    public:
        serveragent();
    public slots:
        virtual void ConnectToClient();
        virtual void DataArrive();
        virtual void getclicked(int x,int y);

};

#endif // SERVERAGENT_H
