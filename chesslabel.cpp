#include"chesslabel.h"

chesslabel::chesslabel(QWidget *parent,int x,int y):QLabel(parent),x(x),y(y){
    connect(this,SIGNAL(clicked(int,int)),parent,SLOT(getclicked(int,int)));
};
void chesslabel::mouseReleaseEvent(QMouseEvent * ev){
    if(ev != nullptr)
        if(ev->button() == Qt::LeftButton)
        emit clicked(this->x,this->y);
}
