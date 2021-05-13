#ifndef SERVERAGENT_H
#define SERVERAGENT_H

#include"netserver.h"
#include<chrono>
#include<thread>
#include<QPushButton>
class serveragent:public netserver{
    Q_OBJECT
    protected:
        QPushButton* flashButton;
    public:
        serveragent();
    public slots:
        virtual void ConnectToClient();
        virtual void DataArrive();
        void flash();
        virtual void getclicked(int x,int y);

};

#endif // SERVERAGENT_H
