#ifndef CLIENTAGENT_H
#define CLIENTAGENT_H

#include"netclient.h"

class clientagent:public netclient{
    public:
        clientagent();
        void sendinfo();
    public slots:
        virtual void DataArrive();
    public slots:
        virtual void getclicked(int x,int y);
};

#endif // CLIENTAGENT_H
