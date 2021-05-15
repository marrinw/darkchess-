#include"agent.h"

agent::agent(){
    this->side=1;
    this->setWindowTitle("人机对战");
}
void agent::getclicked(int x,int y){
    if(this->chessb.getplayernow()!=this->side){
        this->chessb.func(x,y);
        this->print();
        this->repaint();
    }

    if(this->chessb.getplayernow()==this->side&&this->chessb.endgame()==3){
        std::this_thread::sleep_for(std::chrono::milliseconds(550));
        this->cal(this->side);
        this->print();
    }
}


void agent::cal(bool agentSide){
    this->chessb.cal(agentSide);
}
