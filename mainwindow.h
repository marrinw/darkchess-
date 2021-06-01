#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include"pvp.h"
#include"agent.h"
#include"agentvsagent.h"
#include"netserver.h"
#include"netclient.h"
#include"serveragent.h"
#include"clientagent.h"
#include"clientagentB.h"
#include"ConnectedServer.h"
#include<QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;
        QPushButton* pushButton1;
        QPushButton* pushButton2;
        QPushButton* pushButton3;
        QPushButton* pushButton4;
        QPushButton* pushButton5;
        QPushButton* pushButton6;
        QPushButton* pushButton7;
        QPushButton* pushButton8;
        QPushButton* pushButton9;
        QPushButton* pushButton10;
        QPushButton* showHelpButton;
        QLabel* picLabel;
        QLabel* titlePicLabel;
        pvp* game1;
        agent* game2;
        agentvsagent* game3;
        netserver* game4;
        netclient* game5;
        serveragent* game6;
        clientagent* game7;
        clientagent* game8;
        clientagentB* game9;
        connectedServer *game10;
    private slots:
        void creategame1();
        void creategame2();
        void creategame3();
        void creategame4();
        void creategame5();
        void creategame6();
        void creategame7();
        void creategame8();
        void creategame9();
        void creategame10();
        void showHelpMessage();
};
#endif // MAINWINDOW_H
