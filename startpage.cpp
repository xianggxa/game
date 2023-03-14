#include "startpage.h"
#include <QPainter>
#include <QPushButton>
#include <QPixmap>
#include <QPaintEvent>


startpage::startpage(QWidget *parent)
    : QMainWindow(parent)
{
    //设置固定大小
    setFixedSize(WINDOW_LENGTH,WINDOW_WIDTH);

    //设置窗口图标
    setWindowIcon(QIcon(":/source/plane1.png"));

    //设置窗口标题
    setWindowTitle("LEO");


    //创建按钮
    QPushButton *introduce_game=new QPushButton;
    introduce_game->setParent(this);
    introduce_game->setGeometry(910,550,120,40);//位置和大小
    introduce_game->setFocusPolicy(Qt::NoFocus);
    introduce_game->setStyleSheet("QPushButton{border-image:url(:/source/intro_button1.png);}"
                                  "QPushButton:hover{border-image:url(:/source/intro_button2.png);}");
    //参数1：信号发送者 参数2：发送的信号 参数3:信号的接收者 参数4：处理的槽函数
    introduce* transmit1 = new introduce();

    QObject::connect(introduce_game,SIGNAL(clicked()),transmit1,SLOT(show_introduce()));
    QObject::connect(introduce_game,SIGNAL(clicked()),this,SLOT(close()));
    connect(transmit1,SIGNAL(mySignal()),this,SLOT(showpage()));


    QPushButton *start_game=new QPushButton;
    start_game->setParent(this);
    start_game->setGeometry(910,650,120,40);//位置和大小
    start_game->setFocusPolicy(Qt::NoFocus);
    start_game->setStyleSheet("QPushButton{border-image:url(:/source/startbutton1.png);}"
                              "QPushButton:hover{border-image:url(:/source/startbutton2.png);}");
    mainscene* transmit2=new mainscene();
    QObject::connect(start_game,SIGNAL(clicked()),transmit2,SLOT(open_page()));
    QObject::connect(start_game,SIGNAL(clicked()),this,SLOT(hidepage()));

    QPushButton *quit_game=new QPushButton;
    quit_game->setParent(this);
    quit_game->setGeometry(910,750,120,40);//位置和大小
    quit_game->setFocusPolicy(Qt::NoFocus);
    quit_game->setStyleSheet("QPushButton{border-image:url(:/source/exitbutton1.png);}"
                             "QPushButton:hover{border-image:url(:/source/exitbutton2.png);}");
    connect(quit_game,&QPushButton::clicked,this,&startpage::close);

}

startpage::~startpage()
{

}

void startpage:: paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/source/background2.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void startpage::hidepage()
{
    this->close();
}
void startpage::showpage()
{
    this->show();
}
