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


class pvp : public QMainWindow
{
    Q_OBJECT

    public:
        pvp(QWidget *parent = nullptr);
        int print();
    public slots:
        virtual void getclicked(int x,int y);

    protected:
        chessboard chessb;
        chesslabel* chessl[4][8];
        QLabel* showPlayerLabel;

};

#endif // PVP_H
