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
        QPushButton* flashButton;
    public:
        netserver();
        ~netserver();
        void sendinfo();
    public slots:
        virtual void ConnectToClient();
        virtual void DataArrive();
    public slots:
        virtual void getclicked(int x,int y);
        void flash();
};


#endif // NETSERVER_H
