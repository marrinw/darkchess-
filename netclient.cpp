#include"netclient.h"


netclient::netclient(){
    this->clientSide=1;
    this->setWindowTitle("客户端黑人");
    socket=new QTcpSocket(this);
    socket->connectToHost(QHostAddress("127.0.0.1"),8080);
    connect(socket, SIGNAL(readyRead()), this, SLOT(DataArrive()));
}
netclient::~netclient(){
    delete this->socket;
}
void netclient::DataArrive(){
    QByteArray buffer = socket->readAll();
    if(buffer.size()==193){
        int i=0;
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
        int ifend=this->print();
        this->repaint();
        this->repaint();
        if(ifend!=3){
            this->socket->close();
        }
    }
}
void netclient::getclicked(int x,int y){
    char info[2];
    info[0]=x;
    info[1]=y;
    this->socket->write(info,2);

}

