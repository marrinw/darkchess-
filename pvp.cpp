#include"pvp.h"
#include<QMessageBox>

pvp::pvp(QWidget *parent):QMainWindow(parent){
    this->setWindowTitle("人人对战");
    this->setFixedSize(1250,500);
    this->showpicLabel=new QLabel(this);
    this->showpicLabel->resize(200,200);
    this->showpicLabel->move(1050,300);
    QImage img;
    img.load(QString("pic.jpg"));
    this->showpicLabel->setPixmap(QPixmap::fromImage(img));

    this->chessb.initialize();
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++){
            this->chessl[i][j]=new chesslabel(this,j,i);
            this->chessl[i][j]->resize(60,60);
            this->chessl[i][j]->move(3+j*63,50+i*63);
        }
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++){
            this->deadchessl[i][j]=new QLabel(this);
            this->deadchessl[i][j]->resize(60,60);
            this->deadchessl[i][j]->move(550+j*63,50+i*63);
        }
    }
    this->showboard=new QLabel(this);
    this->showboard->move(10,10);
    this->showboard->resize(40,20);
    QFont ft;
    ft.setFamily("楷体");
    this->showboard->setFont(ft);
    this->showboard->setText("棋盘");
    this->showdeadboard=new QLabel(this);
    this->showdeadboard->move(600,10);
    this->showdeadboard->resize(80,20);
    this->showdeadboard->setFont(ft);
    this->showdeadboard->setText("棋子尸体");
    this->showPlayerLabel=new QLabel(this);
    this->showPlayerLabel->move(20,300);
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
                    ft.setFamily("楷体");
                    ft.setBold(true);
                    ft.setPointSize(20);
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
    for(int i=0;i<4;i++){
            for(int j=0;j<8;j++){
                if(!this->chessb.getdeadchessdeck(j,i).getid()){
                    QPalette pe;
                    pe.setColor(QPalette::Background,Qt::white);
                    this->deadchessl[i][j]->setPalette(pe);

                    this->deadchessl[i][j]->setAutoFillBackground(true);
                    this->deadchessl[i][j]->setText("");
                }else if(!this->chessb.getdeadchessdeck(j,i).getvisible()){
                    QPalette pe;
                    pe.setColor(QPalette::Background,Qt::black);
                    this->deadchessl[i][j]->setPalette(pe);
                    this->deadchessl[i][j]->setAutoFillBackground(true);
                    this->deadchessl[i][j]->setText("");
                }else{
                    QFont ft;
                    ft.setFamily("楷体");
                    ft.setBold(true);
                    ft.setPointSize(20);
                    this->deadchessl[i][j]->setFont(ft);
                    QPalette pe;
                    pe.setColor(QPalette::Background,Qt::white);
                    if(this->chessb.getdeadchessdeck(j,i).getside()){
                        pe.setColor(QPalette::WindowText,Qt::black);
                    }else{
                        pe.setColor(QPalette::WindowText,Qt::red);
                    }
                    this->deadchessl[i][j]->setPalette(pe);
                    switch (this->chessb.getdeadchessdeck(j,i).getid()) {
                        case 1:
                            if(!this->chessb.getdeadchessdeck(j,i).getside()){
                                this->deadchessl[i][j]->setText(" 帅");
                            }else{
                                this->deadchessl[i][j]->setText(" 将");
                            }
                            break;
                        case 2:
                            if(!this->chessb.getdeadchessdeck(j,i).getside()){
                                this->deadchessl[i][j]->setText(" 仕");
                            }else{
                                this->deadchessl[i][j]->setText(" 士");
                            }
                            break;
                        case 3:
                            if(!this->chessb.getdeadchessdeck(j,i).getside()){
                                this->deadchessl[i][j]->setText(" 相");
                            }else{
                                this->deadchessl[i][j]->setText(" 象");
                            }
                            break;
                        case 4:
                            this->deadchessl[i][j]->setText(" 车");
                            break;
                        case 5:
                            this->deadchessl[i][j]->setText(" 马");
                            break;
                        case 6:
                            this->deadchessl[i][j]->setText(" 炮");
                            break;
                        case 7:
                            if(!this->chessb.getdeadchessdeck(j,i).getside()){
                                this->deadchessl[i][j]->setText(" 兵");
                            }else{
                                this->deadchessl[i][j]->setText(" 卒");
                            }
                            break;
                    }
                }
            }
        }
    QString showstring;
    if(this->chessb.getplayernow()){
        showstring="黑方执子";
    }else{
        showstring="红方执子";
    }
    this->showPlayerLabel->setText(showstring);
    QFont ft;
    ft.setFamily("楷体");
    this->showPlayerLabel->setFont(ft);
    this->repaint();
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

    return ifend;
}

void pvp::getclicked(int x,int y){
    this->chessb.func(x,y);
    this->print();
}
