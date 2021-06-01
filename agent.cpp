#include"agent.h"

agent::agent(){
    srand(time(0));
    this->side=rand()%2;
    this->setWindowTitle("人机对战");
    this->showside=new QLabel(this);
    this->showside->move(20,400);
    this->showside->resize(160,50);
    this->flashbutton=new QPushButton(this);
    this->flashbutton->move(185,400);
    this->flashbutton->resize(180,60);
    this->flashbutton->setText("刷新棋盘(如果卡了)");
    QImage img;
    img.load(QString("renji.PNG"));
    this->showGameTypeLabel->setPixmap(QPixmap::fromImage(img));
    QFont ft;
    ft.setFamily("楷体");
    ft.setBold(true);
    ft.setPointSize(18);
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
    connect(this->flashbutton,SIGNAL(clicked(bool)),this,SLOT(flash()));
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

void agent::flash(){
    this->chessb.setduringfuncZero();
    this->print();
}
