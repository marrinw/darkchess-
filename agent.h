#ifndef AGENT_H
#define AGENT_H

#include"pvp.h"
#include<chrono>
#include<qlabel>
#include<thread>
#include<QPushButton>

class agent:public pvp{
    Q_OBJECT
    protected:
        bool side;
        QLabel* showside;
        QPushButton* flashbutton;
    public:
        agent();

    public slots:
        virtual void getclicked(int x,int y);
        void flash();

};

#endif // AGENT_H
