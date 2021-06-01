#ifndef PVP_H
#define PVP_H

#include <QMainWindow>
#include<QLabel>
#include<QImage>
#include<QPixmap>
#include<QString>
#include<QMessageBox>
#include<bits/stdc++.h>
#include<chessboard.h>
#include<chesslabel.h>
#include <QMouseEvent>
#include<QImage>
#include<QPixmap>

class pvp : public QMainWindow
{
    Q_OBJECT

    public:
        QLabel *showGameTypeLabel;
        pvp(QWidget *parent = nullptr);
        int print();
    public slots:
        virtual void getclicked(int x,int y);

    protected:
        QLabel* chessPicLabel;
        QLabel* showpicLabel;
        chessboard chessb;
        chesslabel* chessl[4][8];
        QLabel* deadchessl[4][8];
        QLabel* showPlayerLabel;
        QLabel* showboard;
        QLabel* showdeadboard;

};

#endif // PVP_H
