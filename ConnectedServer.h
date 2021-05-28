#ifndef CONNECTEDSERVER_H
#define CONNECTEDSERVER_H

#include"netserver.h"
#include<QPushButton>

class connectedServer: public pvp{
        Q_OBJECT
    protected:
        bool clientAside;
        bool clientBside;
        QTcpServer* serverB;
        QTcpSocket* socketB;
        QTcpServer* serverA;
        QTcpSocket* socketA;
        QPushButton* flashButton;
        bool isConnected[2];
    public:
        connectedServer();
        ~connectedServer();
        void startGame();
        virtual void getclicked(int x,int y);
        void sendinfo();
    public slots:
        virtual void ConnectToClientB();
        virtual void ADataArrive();
        virtual void BDataArrive();
        virtual void flash();
        virtual void ConnectToClientA();
};

#endif // CONNECTEDSERVER_H
