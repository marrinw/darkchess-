#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include"chessman.h"
#include"assForAgent.h"

class chessboard{
    private:
        int chessRemained[2];
        int chessVisible[2];
        int x1;                     //record the chess ready to do
        int y1;                     //record the chess ready to do
        bool duringfunc;
        bool playernow;
        chessman chessdeck[4][8];
        chessman deadchessdeck[4][8];
        int deadchesscount;
        bool eatdeck[8][8]={
            0,0,0,0,0,0,0,0,
            1,1,1,1,1,1,1,0,
            1,0,1,1,1,1,1,1,
            1,0,0,1,1,1,1,1,
            1,0,0,0,1,1,1,1,
            1,0,0,0,0,0,1,1,
            0,1,1,1,1,0,1,1,
            1,1,0,0,0,0,0,0,
        };
        int valuetable[8]={0,7,6,4,3,2,5,1};
        bool isClient=0;
        
    public:
        void setduringfuncZero();               //duringfnc=0
        void initialize();
        void turn(int x,int y);         //turn a chess to visible
        void justmove(int x,int y,int x2,int y2);   //move a chess to unoccupied
        void killandmove(int x,int y,int x2,int y2);        // a chess kill enemy
        chessman& changechessdeck(int x,int y);   //only used in client: use to change its chessdeck same to server
        chessman& changedeadchessdeck(int x,int y);   //only used in client: use to change its deadchessdeck same to server
        chessman getchessdeck(int x,int y) const;       //use for give info to gui
        chessman getdeadchessdeck(int x,int y) const;   //use for give info to gui
        void func(int x,int y);         //do the chess
        bool canmove(int x,int y,int x2,int y2);        //check if a chess can move to a position
        bool cankill(int x,int y,int x2,int y2);        //check if a chess can kill another
        bool cankill(int x,int y,int xfrom,int yfrom,int xto,int yto);  //check if a chess can kil a chess after its movement
        bool getplayernow();                            // return the current player
        int endgame();      //0=red win, 1=black win, 2=even, 3=continue
        int getchessValue(int x,int y);                 //return the value of a chess(use for agent to decide what to do)
        void cal(bool agentSide);                   //agent calaculate
        void changeplayernow(bool side);            //only used in client :change its current player same to server
        int clientAgentinfo[5];                     //only used in clientAgent: store the calaculation of agent
        void countchess();                              //only used in clientagent: count the chessinfo
        asspos chasepath(int xfrom,int yfrom,int xto,int yto);
        void setCilent();                               //set it a client if it is
        
};

#endif // CHESSBOARD_H
