#include"clientagentB.h"

clientagentB::clientagentB(){
    this->chessb.setCilent();
    this->setWindowTitle("客v客B机");
    this->flashButton=new QPushButton(this);
    this->flashButton->setFixedSize(250,80);
    this->flashButton->move(20,400);
    this->flashButton->setText("刷新棋盘（如果卡了或不同步）");
    socket=new QTcpSocket(this);
    socket->connectToHost(QHostAddress("127.0.0.1"),8081);
    this->showSide=new QLabel(this);
    this->showSide->resize(140,50);
    this->showSide->move(290,400);
    srand(time(0));
    this->chessb.setCilent();
    connect(this->flashButton,SIGNAL(clicked()),this,SLOT(flash()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(DataArrive()));
}
clientagentB::~clientagentB(){
    this->socket->close();
    delete this->socket;
}

    void clientagentB::DataArrive(){
    QByteArray buffer = socket->readAll();
    if(buffer.size()==194){
        int i=0;
        this->clientSide=buffer[0]-'0';
        i++;
        if(this->clientSide){
            this->showSide->setText("你是黑子");
        }else if(!this->clientSide){
            this->showSide->setText("你是红子");
        }
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
        if(this->chessb.getplayernow()==this->clientSide&&this->chessb.endgame()==3){
            this->chessb.cal((this->clientSide));
            this->sendinfo();
        }
    }
}
void clientagentB::getclicked(int x,int y){

}
void clientagentB::flash(){
    char info[1];
    info[0]=100;
    this->socket->flush();
    this->socket->write(info,1);
}
void clientagentB::sendinfo(){
    char info[4];
    info[0]=this->chessb.clientAgentinfo[1];
    info[1]=this->chessb.clientAgentinfo[2];
    if(this->chessb.clientAgentinfo[0]==0)
        this->socket->write(info,2);
    else{
        info[2]=this->chessb.clientAgentinfo[3];
        info[3]=this->chessb.clientAgentinfo[4];
        this->socket->write(info,4);
    }
}
