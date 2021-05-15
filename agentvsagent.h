#ifndef AGENTVSAGENT_H
#define AGENTVSAGENT_H

#include"agent.h"
#include<QPushButton>

class agentvsagent:public agent{
    Q_OBJECT
    public slots:
        virtual void getclicked(int x,int y);
        void startgame();
        void singleround();
    public:
        agentvsagent();
    protected:
        bool sideA;
        bool sideB;
        QPushButton* startButton;
        QPushButton* singleRoundButton;

};

#endif // AGENTVSAGENT_H
