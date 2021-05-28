#include"ConnectedServer.h"
#include<QPushButton>
connectedServer::connectedServer(){
    this->setWindowTitle("客v客服务器");
    this->isConnected[0]=0;
    this->isConnected[1]=0;
    srand(time(0));
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++){
            this->chessl[i][j]->move(500,500);
        }
    }
    this->showboard->move(500,500);
    this->setFixedSize(450,90);
    this->clientAside=rand()%2;
    this->clientBside=(this->clientAside+1)%2;
    this->serverA=new QTcpServer(this);
    this->serverA->listen(QHostAddress::Any,8080);
    this->flashButton=new QPushButton(this);
    this->flashButton->setFixedSize(250,80);
    this->flashButton->move(5,5);
    this->flashButton->setText("刷新棋盘（如果卡了或不同步）");
    this->flashButton->setDisabled(1);
    this->serverB=new QTcpServer(this);
    this->serverB->listen(QHostAddress::Any,8081);
    connect(serverB,SIGNAL(newConnection()),this,SLOT(ConnectToClientB()));
    connect(serverA,SIGNAL(newConnection()),this,SLOT(ConnectToClientA()));
    connect(this->flashButton,SIGNAL(clicked()),this,SLOT(flash()));

}

void connectedServer::ConnectToClientA(){
    this->socketA=this->serverA->nextPendingConnection();
    this->isConnected[0]=1;
    QMessageBox::information(this,
                             tr("连接A成功"),
                             tr("连接A成功!"));
    this->startGame();

};

connectedServer::~connectedServer(){
    this->socketA->close();
    this->serverA->close();
    delete this->socketA;
    delete this->serverA;
    this->socketB->close();
    this->serverB->close();
    delete this->socketB;
    delete this->serverB;
}

void connectedServer::ConnectToClientB(){
    this->socketB=this->serverB->nextPendingConnection();
    this->isConnected[1]=1;
    QMessageBox::information(this,
                             tr("连接B成功"),
                             tr("连接B成功!"));
    this->startGame();

};
void connectedServer::startGame(){
    if(!this->isConnected[0]||!this->isConnected[1]){
        return;
    }
    this->socketA->flush();
    this->socketB->flush();
    connect(socketA, SIGNAL(readyRead()), this, SLOT(ADataArrive()));
    connect(socketB, SIGNAL(readyRead()), this, SLOT(BDataArrive()));
    this->flashButton->setDisabled(0);
    this->sendinfo();
}
void connectedServer::ADataArrive(){
    QByteArray buffer = socketA->readAll();
    if(int(buffer[0])==100){
        this->sendinfo();
        return;
    }
    if(buffer.size()<5){
        if(this->chessb.getplayernow()==this->clientAside){
            int x=buffer[0];
            int y=buffer[1];
            this->chessb.func(x,y);
            if(buffer.size()==4){
                x=buffer[2];
                y=buffer[3];
                this->chessb.func(x,y);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
            this->print();
            this->repaint();
            this->sendinfo();
        }
    }
}
void connectedServer::BDataArrive(){
    QByteArray buffer = socketB->readAll();
    if(int(buffer[0])==100){
        this->sendinfo();
        return;
    }
    if(buffer.size()<5){
        if(this->chessb.getplayernow()==this->clientBside){
            int x=buffer[0];
            int y=buffer[1];
            this->chessb.func(x,y);
            if(buffer.size()==4){
                x=buffer[2];
                y=buffer[3];
                this->chessb.func(x,y);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
            this->print();
            this->repaint();
            this->sendinfo();
        }
    }
}
void connectedServer::getclicked(int x,int y){
    return;
}
void connectedServer::sendinfo(){
    this->socketA->flush();
    this->socketB->flush();
    char info[194];
    int i=0;
    info[0]=this->clientAside+'0';
    i++;
    for(int j=0;j<4;j++){
        for(int k=0;k<8;k++){
            info[i]=this->chessb.getchessdeck(k,j).getid()+'0';
            i++;
            info[i]=this->chessb.getchessdeck(k,j).getside()+'0';
            i++;
            info[i]=this->chessb.getchessdeck(k,j).getvisible()+'0';
            i++;
        }
    }
    info[i]=this->chessb.getplayernow()+'0';
    i++;
    for(int j=0;j<4;j++){
        for(int k=0;k<8;k++){
            info[i]=this->chessb.getdeadchessdeck(k,j).getid()+'0';
            i++;
            info[i]=this->chessb.getdeadchessdeck(k,j).getside()+'0';
            i++;
            info[i]=this->chessb.getdeadchessdeck(k,j).getvisible()+'0';
            i++;
        }
    }
    int k;
    do{
        this->socketA->flush();
        k=this->socketA->write(info,194);
    }while(k!=194);
    info[0]=this->clientBside+'0';
    do{
        this->socketB->flush();
        k=this->socketB->write(info,194);
    }while(k!=194);
}

void connectedServer::flash(){
    this->sendinfo();
}
