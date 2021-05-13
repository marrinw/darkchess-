#ifndef _CHESSLABEL_H
#define _CHESSLABEL_H

#include<bits/stdc++.h>
#include<QLabel>
#include<QImage>
#include<QPixmap>
#include<QString>
#include<QMessageBox>
#include"chessboard.h"
#include <QMouseEvent>
class   chesslabel :public QLabel{
        Q_OBJECT
    private:
           int x;
           int y;
           void mouseReleaseEvent(QMouseEvent * ev);
    public:
        chesslabel(QWidget *parent,int x,int y);
    signals:
        void clicked(int x,int y);

};




#endif // CHESSLABEL_H
