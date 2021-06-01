#include"netserver.h"
#include<QPushButton>
netserver::netserver(){
    srand(time(0));
    this->serverSide=rand()%2;
    this->setWindowTitle("服务器端人");
    this->server=new QTcpServer(this);
    this->server->listen(QHostAddress::Any,8080);
    this->flashButton=new QPushButton(this);
    this->flashButton->setFixedSize(250,80);
    this->flashButton->move(20,400);
    this->flashButton->setText("刷新棋盘（如果卡了或不同步）");
    this->flashButton->setDisabled(1);
    this->showSide=new QLabel(this);
    this->showSide->resize(160,50);
    this->showSide->move(290,400);
    QImage img;
    img.load(QString("fuwuduanren.PNG"));
    this->showGameTypeLabel->setPixmap(QPixmap::fromImage(img));
    QFont ft;
    ft.setFamily("楷体");
    ft.setBold(true);
    ft.setPointSize(16);
    this->showSide->setFont(ft);
    if(this->serverSide){
        this->showSide->setText("你是黑子");
    }else if(!this->serverSide){
        this->showSide->setText("你是红子");
    }
    connect(this->flashButton,SIGNAL(clicked()),this,SLOT(flash()));
    connect(server,SIGNAL(newConnection()),this,SLOT(ConnectToClient()));


}

netserver::~netserver(){
    this->socket->close();
    this->server->close();
    delete this->socket;
    delete this->server;
}
void netserver::flash(){
    this->sendinfo();
}

void netserver::DataArrive(){
    QByteArray buffer = socket->readAll();
    if(int(buffer[0])==100){
        this->sendinfo();
        return;
    }
    if(buffer.size()<5){
        if(this->chessb.getplayernow()!=this->serverSide){
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
void netserver::ConnectToClient(){
    this->flashButton->setDisabled(0);
    this->socket=this->server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(DataArrive()));
    this->sendinfo();
    QMessageBox::information(this,
                             tr("连接成功"),
                             tr("连接成功!"));
}
void netserver::sendinfo(){
    this->socket->flush();
    char info[194];
    int i=0;
    info[0]=(this->serverSide+1)%2+'0';
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
        this->socket->flush();
        k=this->socket->write(info,194);
    }while(k!=194);

}
void netserver::getclicked(int x,int y){
    if(this->chessb.getplayernow()==this->serverSide){
        this->chessb.func(x,y);
        this->print();
        this->sendinfo();
    }
}
