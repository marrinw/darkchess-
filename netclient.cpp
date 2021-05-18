#include"netclient.h"
#include<QPushButton>

netclient::netclient(){
    this->chessb.setCilent();
    this->setWindowTitle("客户端人");
    this->flashButton=new QPushButton(this);
    this->flashButton->setFixedSize(250,80);
    this->flashButton->move(20,400);
    this->flashButton->setText("刷新棋盘（如果卡了或不同步）");
    socket=new QTcpSocket(this);
    socket->connectToHost(QHostAddress("127.0.0.1"),8080);
    this->showSide=new QLabel(this);
    this->showSide->resize(140,50);
    this->showSide->move(290,400);
    connect(this->flashButton,SIGNAL(clicked()),this,SLOT(flash()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(DataArrive()));

}
netclient::~netclient(){
    this->socket->close();
    delete this->socket;
}
void netclient::DataArrive(){
    QByteArray buffer = socket->readAll();
    if(buffer.size()==194){
        int i=0;
        this->clientSide=buffer[i]-'0';
        if(this->clientSide){
            this->showSide->setText("你是黑子");
        }else if(!this->clientSide){
            this->showSide->setText("你是红子");
        }
        i++;
        for(int j=0;j<4;j++){
            for(int k=0;k<8;k++){
                this->chessb.changechessdeck(k,j).changeid(buffer[i]-'0');
                i++;
                this->chessb.changechessdeck(k,j).changeside(buffer[i]-'0');
                i++;
                this->chessb.changechessdeck(k,j).changevisible(buffer[i]-'0');
                i++;
            }
        }
        this->chessb.changeplayernow(buffer[i]-'0');
        i++;
        for(int j=0;j<4;j++){
            for(int k=0;k<8;k++){
                this->chessb.changedeadchessdeck(k,j).changeid(buffer[i]-'0');
                i++;
                this->chessb.changedeadchessdeck(k,j).changeside(buffer[i]-'0');
                i++;
                this->chessb.changedeadchessdeck(k,j).changevisible(buffer[i]-'0');
                i++;
            }
        }
        this->chessb.countchess();
        this->print();
        this->repaint();
        this->repaint();
    }
}
void netclient::getclicked(int x,int y){
    char info[2];
    info[0]=x;
    info[1]=y;
    this->socket->write(info,2);

}
void netclient::flash(){
    char info[1];
    info[0]=100;
    this->socket->flush();
    this->socket->write(info,1);
}
