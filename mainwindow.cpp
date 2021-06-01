#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QPushButton>
#include<QFont>
#include<QPalette>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFont ft;
    ft.setBold(true);
    ft.setPointSize(9);
    ft.setFamily("楷体");
    QPalette palette(Qt::white);
    this->setWindowTitle("象棋暗棋");
    this->setFixedSize(400,300);
    this->pushButton1=new QPushButton(this);
    this->pushButton1->setText("人人对战");
    this->pushButton1->setFont(ft);
    this->pushButton1->move(5,5);
    this->pushButton1->setFlat(true);
    this->pushButton1->resize(100,45);
    this->pushButton2=new QPushButton(this);
    this->pushButton2->setText("人机对战");
    this->pushButton2->setFont(ft);
    this->pushButton2->setFlat(true);
    this->pushButton2->move(115,5);
    this->pushButton2->resize(100,45);
    this->pushButton3=new QPushButton(this);
    this->pushButton3->setText("机机对战");
    this->pushButton3->setFont(ft);
    this->pushButton3->setFlat(true);
    this->pushButton3->move(225,5);
    this->pushButton3->resize(100,45);
    this->pushButton4=new QPushButton(this);
    this->pushButton4->setText("服务器端人");
    this->pushButton4->setFont(ft);
    this->pushButton4->setFlat(true);
    this->pushButton4->move(5,55);
    this->pushButton4->resize(100,45);
    this->pushButton5=new QPushButton(this);
    this->pushButton5->setText("客户端人");
    this->pushButton5->setFont(ft);
    this->pushButton5->setFlat(true);
    this->pushButton5->move(115,55);
    this->pushButton5->resize(100,45);
    this->pushButton6=new QPushButton(this);
    this->pushButton6->setText("服务端机");
    this->pushButton6->setFont(ft);
    this->pushButton6->setFlat(true);
    this->pushButton6->move(225,55);
    this->pushButton6->resize(100,45);
    this->pushButton7=new QPushButton(this);
    this->pushButton7->setText("客户端机");
    this->pushButton7->setFont(ft);
    this->pushButton7->setFlat(true);
    this->pushButton7->move(5,95);
    this->pushButton7->resize(100,45);
    this->pushButton8=new QPushButton(this);
    this->pushButton8->setText("客v客A机");
    this->pushButton8->setFont(ft);
    this->pushButton8->setFlat(true);
    this->pushButton8->move(115,95);
    this->pushButton8->resize(100,45);
    this->pushButton9=new QPushButton(this);
    this->pushButton9->setText("客v客B机");
    this->pushButton9->setFont(ft);
    this->pushButton9->setFlat(true);
    this->pushButton9->move(225,95);
    this->pushButton9->resize(100,45);
    this->pushButton10=new QPushButton(this);
    this->pushButton10->setText("客v客服务器");
    this->pushButton10->setFont(ft);
    this->pushButton10->setFlat(true);
    this->pushButton10->move(5,145);
    this->pushButton10->resize(120,45);
    this->showHelpButton=new QPushButton(this);
    this->showHelpButton->move(5,210);
    this->showHelpButton->resize(100,45);
    this->showHelpButton->setFlat(true);
    this->showHelpButton->setFont(ft);
    this->showHelpButton->setText("说明帮助");
    this->titlePicLabel=new QLabel(this);
    this->titlePicLabel->resize(155,70);
    this->titlePicLabel->move(102,200);
    this->picLabel=new QLabel(this);
    this->picLabel->move(250,150);
    this->picLabel->resize(150,150);
    QImage img;
    img.load(QString("chesspic.jpg"));
    this->picLabel->setPixmap(QPixmap::fromImage(img));
    img.load(QString("titlepic.PNG"));
    this->titlePicLabel->setPixmap(QPixmap::fromImage(img));

    this->autoFillBackground();

    this->setPalette(palette);
    connect(this->pushButton1,SIGNAL(clicked(bool)),this,SLOT(creategame1()));
    connect(this->pushButton2,SIGNAL(clicked(bool)),this,SLOT(creategame2()));
    connect(this->pushButton3,SIGNAL(clicked(bool)),this,SLOT(creategame3()));
    connect(this->pushButton4,SIGNAL(clicked(bool)),this,SLOT(creategame4()));
    connect(this->pushButton5,SIGNAL(clicked(bool)),this,SLOT(creategame5()));
    connect(this->pushButton6,SIGNAL(clicked(bool)),this,SLOT(creategame6()));
    connect(this->pushButton7,SIGNAL(clicked(bool)),this,SLOT(creategame7()));
    connect(this->pushButton8,SIGNAL(clicked(bool)),this,SLOT(creategame8()));
    connect(this->pushButton9,SIGNAL(clicked(bool)),this,SLOT(creategame9()));
    connect(this->pushButton10,SIGNAL(clicked(bool)),this,SLOT(creategame10()));
    connect(this->showHelpButton,SIGNAL(clicked(bool)),this,SLOT(showHelpMessage()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::creategame1(){
    this->game1=new pvp;
    this->game1->show();
}
void MainWindow::creategame2(){
    this->game2=new agent;
    this->game2->show();
}
void MainWindow::creategame3(){
    this->game3=new agentvsagent;
    this->game3->show();
}
void MainWindow::creategame4(){
    this->game4=new netserver;
    this->game4->show();
}
void MainWindow::creategame5(){
    this->game5=new netclient;
    this->game5->show();
}
void MainWindow::creategame6(){
    this->game6=new serveragent;
    this->game6->show();
}
void MainWindow::creategame7(){
    this->game7=new clientagent;
    this->game7->show();
}
void MainWindow::creategame8(){
    this->game8=new clientagent;
    this->game8->setWindowTitle("客v客A机");
    QImage img;
    img.load(QString("kea.PNG"));
    this->game8->showGameTypeLabel->setPixmap(QPixmap::fromImage(img));
    this->game8->show();
}
void MainWindow::creategame9(){
    this->game9=new clientagentB;
    this->game9->show();
}
void MainWindow::creategame10(){
    this->game10=new connectedServer;
    this->game10->show();
}



void MainWindow::showHelpMessage(){
    QMessageBox::information(this,tr("help"), tr("此暗棋的炮只能打不能空走\n当一方有棋子不能被对方任何棋子吃时，游戏结束\n如果一方只剩下炮，则和棋\n打开新的cs时请关闭程序重新打开\ncs程序占用8080和8081端口\ncvc时先打开server"));
}
