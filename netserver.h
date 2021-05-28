#ifndef NETSERVER_H
#define NETSERVER_H

#include<QTcpServer>
#include<QTcpSocket>
#include"pvp.h"
#include<chrono>
#include<thread>
#include<QLabel>

class netserver:public pvp{
    Q_OBJECT
    protected:
        bool serverSide;
        QTcpServer* server;
        QTcpSocket* socket;
        QPushButton* flashButton;
        QLabel* showSide;
    public:
        netserver();
        ~netserver();
        void sendinfo();
    public slots:
        virtual void ConnectToClient();
        virtual void DataArrive();
    public slots:
        virtual void getclicked(int x,int y);
        virtual void flash();
};


#endif // NETSERVER_H
