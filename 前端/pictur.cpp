#include "pictur.h"
#include <QPaintEvent>
#include <QPainter>

pictur::pictur(QWidget *parent) : QMainWindow(parent)
{


 this->setFixedSize(896,540);
 this->setWindowTitle("决策树");
 this->setWindowIcon(QIcon(":/new\\w.jpg"));




}
void pictur::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    QPixmap pix;
    pix.load(":/new/fine.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}


