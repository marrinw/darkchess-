#ifndef AGENT_H
#define AGENT_H

#include"pvp.h"
#include<chrono>
#include<thread>

class agent:public pvp{
    Q_OBJECT
    protected:
        bool side;
        //int calvalue(int x,int y);
    public:
        void cal(bool agentSide);
        agent();

    public slots:
        virtual void getclicked(int x,int y);

};

#endif // AGENT_H
