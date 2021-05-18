#ifndef AGENTVSAGENT_H
#define AGENTVSAGENT_H

#include"agent.h"
#include<QPushButton>
#include<QLabel>

class agentvsagent:public pvp{
    Q_OBJECT
    public slots:
        virtual void getclicked(int x,int y);
        void startgame();
        void singleround();
        void fiveround();
    public:
        agentvsagent();
    protected:
        bool sideA;
        bool sideB;
        QPushButton* startButton;
        QPushButton* singleRoundButton;
        QPushButton* fiveRoundGameButton;

};

#endif // AGENTVSAGENT_H
