#include "introduce.h"
#include <QPainter>
#include <QPaintEvent>
#include "startpage.h"

introduce::introduce(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("介绍");
    this->setFixedSize(WINDOW_LENGTH,WINDOW_WIDTH);
    setWindowIcon(QIcon(":/source/plane1.png"));
    back_start2.setParent(this);
    back_start2.setGeometry(890,730,120,40);//位置和大小
    back_start2.setFocusPolicy(Qt::NoFocus);
    back_start2.setStyleSheet("QPushButton{border-image:url(:/source/backbutton1.png);}"
                              "QPushButton:hover{border-image:url(:/source/backbutton2.png);}");
    connect(&back_start2,&QPushButton::clicked,this,&introduce::changeSlot);
    connect(&back_start2,&QPushButton::clicked,this,&introduce::close);
}

void introduce:: paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    QPixmap pix;
    pix.load(":/source/introduce_background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/source/game_introduce.png");
    pix=pix.scaled(pix.width()*0.7,pix.height()*0.7);
    painter.drawPixmap(550,20,pix);
    pix.load(":/source/introduce_text.png");
    painter.drawPixmap(450,200,pix);
}

void introduce::show_introduce()
{
    this->show();
}
void introduce::changeSlot()
{
    emit mySignal();
}
