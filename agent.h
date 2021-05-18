#ifndef AGENT_H
#define AGENT_H

#include"pvp.h"
#include<chrono>
#include<qlabel>
#include<thread>

class agent:public pvp{
    Q_OBJECT
    protected:
        bool side;
        QLabel* showside;
    public:
        agent();

    public slots:
        virtual void getclicked(int x,int y);

};

#endif // AGENT_H
