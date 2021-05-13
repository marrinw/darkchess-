#include<agentvsagent.h>

void agentvsagent::getclicked(int x,int y){

};
agentvsagent::agentvsagent(){
    this->sideA=0;
    this->sideB=1;
    this->setWindowTitle("机机对战");
    this->startButton=new QPushButton("开始机机对战",this);
    this->startButton->move(980,300);
    this->startButton->resize(140,50);
    connect(this->startButton,SIGNAL(clicked()),this,SLOT(startgame()));
}

void agentvsagent::startgame(){
    while(this->chessb.endgame()==3){
        if(this->chessb.getplayernow()==0){
            this->cal(this->sideA);
            this->print();
            this->repaint();
            std::this_thread::sleep_for(std::chrono::milliseconds(550));
        }else if(this->chessb.getplayernow()==1){
            this->cal(this->sideB);
            this->print();
            this->repaint();
            std::this_thread::sleep_for(std::chrono::milliseconds(550));
        }
    }
}
