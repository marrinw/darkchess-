#ifndef CLIENTAGENTB_H
#define CLIENTAGENTB_H

#include"clientagent.h"
class clientagentB: public pvp{
    Q_OBJECT
    protected:
        bool clientSide;
        QTcpSocket* socket;
        QPushButton* flashButton;
        QLabel* showSide;
    public:
        clientagentB();
        ~clientagentB();
        void sendinfo();
    public slots:
        virtual void DataArrive();
    public slots:
        virtual void getclicked(int x,int y);
        void flash();

};

#endif // CLIENTAGENTB_H
