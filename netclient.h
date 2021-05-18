#ifndef NETCLIENT_H
#define NETCLIENT_H

#include<QTcpSocket>
#include"pvp.h"
#include<QHostAddress>
#include<QPushButton>
class netclient:public pvp{
    Q_OBJECT
    protected:
        bool clientSide;
        QTcpSocket* socket;
        QPushButton* flashButton;
    public:
        netclient();
        ~netclient();
    public slots:
        virtual void DataArrive();
    public slots:
        virtual void getclicked(int x,int y);
        void flash();
};

#endif // NETCLIENT_H
