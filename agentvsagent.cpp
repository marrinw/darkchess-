#include<agentvsagent.h>

void agentvsagent::getclicked(int x,int y){
    return;

};
agentvsagent::agentvsagent(){
    this->sideA=0;
    this->sideB=1;
    this->setWindowTitle("机机对战");
    this->startButton=new QPushButton("开始对战快速",this);
    this->startButton->move(20,400);
    this->startButton->resize(140,50);
    this->singleRoundButton=new QPushButton("一回合",this);
    this->singleRoundButton->move(190,400);
    this->singleRoundButton->resize(140,50);
    this->fiveRoundGameButton=new QPushButton("五回合",this);
    this->fiveRoundGameButton->resize(150,50);
    this->fiveRoundGameButton->move(350,400);
    connect(this->startButton,SIGNAL(clicked()),this,SLOT(startgame()));
    connect(this->singleRoundButton,SIGNAL(clicked()),this,SLOT(singleround()));
    connect(this->fiveRoundGameButton,SIGNAL(clicked()),this,SLOT(fiveround()));
}

void agentvsagent::startgame(){
    int i=0;
    while(this->chessb.endgame()==3){
        if(this->chessb.getplayernow()==0){
            this->chessb.cal(this->sideA);
            i++;
            this->print();
            this->repaint();
            //std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }else if(this->chessb.getplayernow()==1){
            this->chessb.cal(this->sideB);
            i++;
            this->print();
            this->repaint();
            //std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

void agentvsagent::singleround(){
    int i=0;
    while(this->chessb.endgame()==3&&i<2){
        if(this->chessb.getplayernow()==0){
            this->chessb.cal(this->sideA);
            this->print();
            this->repaint();
            i++;
            std::this_thread::sleep_for(std::chrono::milliseconds(550));
        }else if(this->chessb.getplayernow()==1){
            this->chessb.cal(this->sideB);
            this->print();
            this->repaint();
            i++;
            std::this_thread::sleep_for(std::chrono::milliseconds(550));
        }
    }
}
void agentvsagent::fiveround(){
    int i=0;
    while(this->chessb.endgame()==3&&i<10){
        if(this->chessb.getplayernow()==0){
            this->chessb.cal(this->sideA);
            i++;
            this->print();
            this->repaint();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }else if(this->chessb.getplayernow()==1){
            this->chessb.cal(this->sideB);
            i++;
            this->print();
            this->repaint();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
}

