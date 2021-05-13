#ifndef NETSERVER_H
#define NETSERVER_H

#include<QTcpServer>
#include<QTcpSocket>
#include"pvp.h"
#include<chrono>
#include<thread>

class netserver:public pvp{
    Q_OBJECT
    protected:
        bool serverSide;
        QTcpServer* server;
        QTcpSocket* socket;
    public:
        netserver();
        void sendinfo();
    public slots:
        virtual void ConnectToClient();
        virtual void DataArrive();
    public slots:
        virtual void getclicked(int x,int y);
};


#endif // NETSERVER_H
