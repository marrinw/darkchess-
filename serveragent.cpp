#include"serveragent.h"

serveragent::serveragent(){
    this->setWindowTitle("服务器端红机");
    this->flashButton=new QPushButton(this);
    this->flashButton->setFixedSize(250,80);
    this->flashButton->move(20,400);
    this->flashButton->setText("刷新棋盘（如果卡了或不同步）");
    connect(this->flashButton,SIGNAL(clicked()),this,SLOT(flash()));
}
void serveragent::ConnectToClient(){
    this->socket=this->server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(DataArrive()));
    this->print();
    this->sendinfo();
    //std::this_thread::sleep_for(std::chrono::milliseconds(550));
    QMessageBox::information(this,
                             tr("连接成功"),
                             tr("连接成功!"));
    this->chessb.cal(this->serverSide);
    //std::this_thread::sleep_for(std::chrono::milliseconds(550));
    this->print();
    this->sendinfo();
}

void serveragent::DataArrive(){
    QByteArray buffer = socket->readAll();
    if(this->chessb.getplayernow()!=this->serverSide){
        int x=buffer[0];
        int y=buffer[1];
        this->chessb.func(x,y);
        if(buffer.size()==4){
            x=buffer[2];
            y=buffer[3];
            this->chessb.func(x,y);
        }
        this->print();
        this->repaint();
        this->sendinfo();
        //std::this_thread::sleep_for(std::chrono::milliseconds(550));
        if(this->chessb.getplayernow()==this->serverSide&&this->chessb.endgame()==3){
            this->chessb.cal(this->serverSide);
            std::this_thread::sleep_for(std::chrono::milliseconds(550));
            int ifend=this->print();
            this->repaint();
            this->sendinfo();
            if(ifend!=3){
                this->socket->close();
                this->server->close();
            }
        }
    }
}
void serveragent::getclicked(int x,int y){
    return;
}
void serveragent::flash(){
    this->sendinfo();
}
