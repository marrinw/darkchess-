#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("象棋暗棋");
    this->setFixedSize(400,300);
    this->pushButton1=new QPushButton(this);
    this->pushButton1->setText("人人对战");
    this->pushButton1->move(5,5);
    this->pushButton1->resize(100,45);
    this->pushButton2=new QPushButton(this);
    this->pushButton2->setText("人机对战");
    this->pushButton2->move(115,5);
    this->pushButton2->resize(100,45);
    this->pushButton3=new QPushButton(this);
    this->pushButton3->setText("机机对战");
    this->pushButton3->move(225,5);
    this->pushButton3->resize(100,45);
    this->pushButton4=new QPushButton(this);
    this->pushButton4->setText("服务器端人");
    this->pushButton4->move(5,55);
    this->pushButton4->resize(100,45);
    this->pushButton5=new QPushButton(this);
    this->pushButton5->setText("客户端人");
    this->pushButton5->move(115,55);
    this->pushButton5->resize(100,45);
    this->pushButton6=new QPushButton(this);
    this->pushButton6->setText("服务端机");
    this->pushButton6->move(225,55);
    this->pushButton6->resize(100,45);
    this->pushButton7=new QPushButton(this);
    this->pushButton7->setText("客户端机");
    this->pushButton7->move(5,95);
    this->pushButton7->resize(100,45);
    this->showHelpButton=new QPushButton(this);
    this->showHelpButton->move(90,200);
    this->showHelpButton->resize(100,45);
    this->showHelpButton->setText("规则帮助");
    connect(this->pushButton1,SIGNAL(clicked(bool)),this,SLOT(creategame1()));
    connect(this->pushButton2,SIGNAL(clicked(bool)),this,SLOT(creategame2()));
    connect(this->pushButton3,SIGNAL(clicked(bool)),this,SLOT(creategame3()));
    connect(this->pushButton4,SIGNAL(clicked(bool)),this,SLOT(creategame4()));
    connect(this->pushButton5,SIGNAL(clicked(bool)),this,SLOT(creategame5()));
    connect(this->pushButton6,SIGNAL(clicked(bool)),this,SLOT(creategame6()));
    connect(this->pushButton7,SIGNAL(clicked(bool)),this,SLOT(creategame7()));
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

void MainWindow::showHelpMessage(){
    QMessageBox::information(this,tr("help"), tr("此暗棋的炮只能打不能空走\n 当一方有棋子不能被对方任何棋子吃时，游戏结束\n打开新的cs时请关闭程序重新打开"));
}
