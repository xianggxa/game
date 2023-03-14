#include "deathpage.h"
#include "mainscene.h"
#include "startpage.h"

deathpage::deathpage(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(WINDOW_LENGTH,WINDOW_WIDTH);
    setWindowTitle(" ");
    setWindowIcon(QIcon(":/source/plane1.png"));

    play_again.setParent(this);
    play_again.setGeometry(900,500,120,40);//位置和大小
    play_again.setFocusPolicy(Qt::NoFocus);
    play_again.setStyleSheet("QPushButton{border-image:url(:/source/onemore1.png);}"
                             "QPushButton:hover{border-image:url(:/source/onemore2.png);}");
    mainscene* transmit3= new mainscene();
    connect(&play_again,&QPushButton::clicked,transmit3,&mainscene::show);
    connect(&play_again,&QPushButton::clicked,this,&deathpage::close);

    backstart.setParent(this);
    backstart.setGeometry(900,600,120,40);//位置和大小
    backstart.setFocusPolicy(Qt::NoFocus);
    backstart.setStyleSheet("QPushButton{border-image:url(:/source/backbutton1.png);}"
                            "QPushButton:hover{border-image:url(:/source/backbutton2.png);}");
    startpage* transmit4=new startpage();
    connect(&backstart,&QPushButton::clicked,transmit4,&startpage::showpage);
    connect(&backstart,&QPushButton::clicked,this,&deathpage::close);
}
void deathpage:: paintEvent(QPaintEvent *)
{
    //创建画家，指定绘图设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/source/die.png");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

}
void deathpage::show_page()
{
    this->show();
}
