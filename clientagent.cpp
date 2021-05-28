#include"clientagent.h"

clientagent::clientagent(){
    srand(time(0));
    this->setWindowTitle("客户端机");
    this->chessb.setCilent();
}

void clientagent::getclicked(int x,int y){
    return;
}

void clientagent::sendinfo(){
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
void clientagent::DataArrive(){
    this->flashButton->setDisabled(0);
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
