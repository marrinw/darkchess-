#include"pvp.h"
#include<QMessageBox>

pvp::pvp(QWidget *parent):QMainWindow(parent){
    this->setWindowTitle("人人对战");
    this->setFixedSize(1250,500);
    this->chessb.initialize();
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++){
            this->chessl[i][j]=new chesslabel(this,j,i);
            this->chessl[i][j]->resize(100,100);
            this->chessl[i][j]->move(5+j*105,5+i*105);
        }
    }
    this->showPlayerLabel=new QLabel(this);
    this->showPlayerLabel->move(1000,300);
    this->showPlayerLabel->resize(120,80);
    this->print();
}
int pvp::print(){
    for(int i=0;i<4;i++){
            for(int j=0;j<8;j++){
                if(!this->chessb.getchessdeck(j,i).getid()){
                    QPalette pe;
                    pe.setColor(QPalette::Background,Qt::white);
                    this->chessl[i][j]->setPalette(pe);

                    this->chessl[i][j]->setAutoFillBackground(true);
                    this->chessl[i][j]->setText("");
                }else if(!this->chessb.getchessdeck(j,i).getvisible()){
                    QPalette pe;
                    pe.setColor(QPalette::Background,Qt::black);
                    this->chessl[i][j]->setPalette(pe);
                    this->chessl[i][j]->setAutoFillBackground(true);
                    this->chessl[i][j]->setText("");
                }else{
                    QFont ft;
                    ft.setPointSize(26);
                    this->chessl[i][j]->setFont(ft);
                    QPalette pe;
                    pe.setColor(QPalette::Background,Qt::white);
                    if(this->chessb.getchessdeck(j,i).getside()){
                        pe.setColor(QPalette::WindowText,Qt::black);
                    }else{
                        pe.setColor(QPalette::WindowText,Qt::red);
                    }
                    this->chessl[i][j]->setPalette(pe);
                    switch (this->chessb.getchessdeck(j,i).getid()) {
                        case 1:
                            if(!this->chessb.getchessdeck(j,i).getside()){
                                this->chessl[i][j]->setText(" 帅");
                            }else{
                                this->chessl[i][j]->setText(" 将");
                            }
                            break;
                        case 2:
                            if(!this->chessb.getchessdeck(j,i).getside()){
                                this->chessl[i][j]->setText(" 仕");
                            }else{
                                this->chessl[i][j]->setText(" 士");
                            }
                            break;
                        case 3:
                            if(!this->chessb.getchessdeck(j,i).getside()){
                                this->chessl[i][j]->setText(" 相");
                            }else{
                                this->chessl[i][j]->setText(" 象");
                            }
                            break;
                        case 4:
                            this->chessl[i][j]->setText(" 车");
                            break;
                        case 5:
                            this->chessl[i][j]->setText(" 马");
                            break;
                        case 6:
                            this->chessl[i][j]->setText(" 炮");
                            break;
                        case 7:
                            if(!this->chessb.getchessdeck(j,i).getside()){
                                this->chessl[i][j]->setText(" 兵");
                            }else{
                                this->chessl[i][j]->setText(" 卒");
                            }
                            break;
                    }
                }
            }
        }
    int ifend=this->chessb.endgame();
        switch (ifend) {
            case 0:
                QMessageBox::information(this,tr("红方胜利"), tr("红方胜利!"));
                break;
            case 1:
                QMessageBox::information(this,tr("黑方胜利"), tr("黑方胜利!"));
                break;
            case 2:
                QMessageBox::information(this,tr("和棋"), tr("和棋!"));
                break;
            default:
                break;
        }
    QString showstring;
    if(this->chessb.getplayernow()){
        showstring="黑方执子";
    }else{
        showstring="红方执子";
    }
    this->showPlayerLabel->setText(showstring);
    return ifend;
}

void pvp::getclicked(int x,int y){
    this->chessb.func(x,y);
    this->print();
}
