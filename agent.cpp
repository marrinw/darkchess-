#include"agent.h"

agent::agent(){
    srand(time(0));
    this->side=rand()%2;
    this->setWindowTitle("人机对战");
    this->showside=new QLabel(this);
    this->showside->move(20,400);
    this->showside->resize(140,50);
    QFont ft;
    ft.setFamily("楷体");
    this->showside->setFont(ft);
    if(this->side){
        this->showside->setText("你是红方");
    }else{
        this->showside->setText("你是黑方");
    }
    if(this->chessb.getplayernow()==this->side&&this->chessb.endgame()==3){
        this->chessb.cal(this->side);
        this->print();
    }
}
void agent::getclicked(int x,int y){
    if(this->chessb.getplayernow()!=this->side){
        this->chessb.func(x,y);
        this->print();
        this->repaint();
    }

    if(this->chessb.getplayernow()==this->side&&this->chessb.endgame()==3){
        std::this_thread::sleep_for(std::chrono::milliseconds(550));
        this->chessb.cal(this->side);
        this->print();
    }
}
