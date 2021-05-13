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

    if(this->chessb.getplayernow()==this->side){
        std::this_thread::sleep_for(std::chrono::milliseconds(550));
        this->cal(this->side);
        this->print();
    }
}

/*int agent::calvalue(int x, int y){
    return this->chessb.getchessValue(x,y);
}*/

void agent::cal(bool agentSide){
    this->chessb.cal(agentSide);
}
