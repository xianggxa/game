#include "mainscene.h"
#include "QtDebug"
#include "QFile"
#include "QTextStream"
#include "config.h"
#include "Qpainter"
#include <time.h>
#include "bullet.h"
#include <QVector>
#include <qmath.h>
#include "miniroom.h"
#include "QPen"
#include "QDebug"
#include <QSound>
#include <QTime>
#include <QLabel>
#include <QDebug>
mainscene::mainscene(QWidget *parent)
    : QWidget(parent)
{//map m;
    InitiScene();
    /*QFile file("D:/qt programme/dick.txt");
    file.open(QIODevice::WriteOnly);
    QTextStream in(&file);
    for(int i=0;i<FIRST_ROOM_SIZE;i++){
        for(int j=0;j<FIRST_ROOM_SIZE;j++)
            in<<m.m_map_first[i][j]<<" ";
        in<<"\n";
    }
    file.close();*/

}
double division(double a, double b)
{
   if( b==0)
   {
      throw "Division by zero condition!";
   }
   return (a/b);
}
mainscene::~mainscene()
{

}

void mainscene::InitiScene()
{
    srand(time(0));
    setFixedSize(WINDOW_LENGTH,WINDOW_WIDTH);
    setWindowTitle("斯卡布罗集市");
    setWindowIcon(QIcon(":/source/plane1.png"));
    m_timer.setInterval(GAME_RATE);
    InitHeroPosition();
    Play_Game();
}
void mainscene::Bomb_UpdatePosition()
{
    //计算爆炸播放的图片
    int num=m_bombs.size();
    for(int i = 0 ; i < num;i++)
    {
        m_bombs[i].Bomb_UpdateInfo();
        if(m_bombs[i].m_index>m_bombs[i].m_max_index[m_bombs[i].m_form])
        {
            m_bombs.remove(i);
            i--;
            num--;
            continue;
        }
    }
}
void mainscene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //绘制背景
    int x=(m_map.m_map_up_left_corner_x-m_map.m_map_corrected_x)/MAGNIFICATION;
    int y=(m_map.m_map_up_left_corner_y-m_map.m_map_corrected_y)/MAGNIFICATION;
    for(;x*MAGNIFICATION<=(m_map.m_map_up_left_corner_x+WINDOW_LENGTH-m_map.m_map_corrected_x);x++){
        for(y=(m_map.m_map_up_left_corner_y-m_map.m_map_corrected_y)/MAGNIFICATION;y*MAGNIFICATION<=(m_map.m_map_up_left_corner_y+WINDOW_WIDTH-m_map.m_map_corrected_y);y++){
            if(m_map.m_map_second[y][x]){//绘制墙的底端
                painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y+4+m_map.m_map_corrected_y,m_map.m_map_wall);
                //补黑墙
                if(!m_map.m_map_second_floor[y+1][x]&&((m_map.m_map_second[y+1][x-1]&&m_map.m_map_second[y+1][x+3])||(m_map.m_map_second[y+1][x-2]&&m_map.m_map_second[y+1][x+2])||(m_map.m_map_second[y+1][x-3]&&m_map.m_map_second[y+1][x+1]))){

                }
                else if((m_map.m_map_second_floor[y-1][x]||m_map.m_map_second_floor[y-1][x-1]||m_map.m_map_second_floor[y-1][x+1])&&!m_map.m_map_second_floor[y+1][x]&&!m_map.m_map_second_floor[y][x-1]&&!m_map.m_map_second_floor[y][x+1])
                    painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y+m_map.m_map_corrected_y,m_map.m_map_wall0[2]);
                else if(!m_map.m_map_second_floor[y][x]&&m_map.m_map_second[y-4][x]&&!m_map.m_map_second[y-1][x])
                    painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y+m_map.m_map_corrected_y,m_map.m_map_wall0[2]);
            }
            else if(m_map.m_map_second_floor[y][x]){
                if(m_map.m_map_second_floor_picture[y][x])
                    painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y+m_map.m_map_corrected_y,m_map.m_map_floor1);
                else painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y+m_map.m_map_corrected_y,m_map.m_map_floor2);
            }else if(!m_map.m_map_second_floor[y][x]&&((m_map.m_map_second[y-2][x]&&m_map.m_map_second[y+2][x])||(m_map.m_map_second[y-1][x]&&m_map.m_map_second[y+3][x])||(m_map.m_map_second[y-3][x]&&m_map.m_map_second[y+1][x])||(m_map.m_map_second[y][x-2]&&m_map.m_map_second[y][x+2])||(m_map.m_map_second[y][x-1]&&m_map.m_map_second[y][x+3])||(m_map.m_map_second[y][x-3]&&m_map.m_map_second[y][x+1]))){
                //道路砖块填补
                painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y+m_map.m_map_corrected_y,m_map.m_map_floor1);
            }

            else   painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y+m_map.m_map_corrected_y,m_map.m_map_wall0[2]);
        }
    }
    //画出子弹
    //迭代器
    QVector<bullet>::iterator iter;
    for (iter=m_map.bullet_message.begin();iter!=m_map.bullet_message.end();iter++)
    {
        int xx=iter->m_x-m_map.m_map_up_left_corner_x,yy=iter->m_y-m_map.m_map_up_left_corner_y;
        painter.drawPixmap(xx+m_map.m_map_corrected_x,yy+m_map.m_map_corrected_y,iter->m_bullet[iter->m_bullet_form]);
    }

    /*int len=m_map.bullet_message.size();
    for(int i=0;i<len;i++)
    {
        int xx=m_map.bullet_message[i].m_x-m_map.m_map_up_left_corner_x,yy=m_map.bullet_message[i].m_y-m_map.m_map_up_left_corner_y;
        painter.drawPixmap(xx+m_map.m_map_corrected_x,yy+m_map.m_map_corrected_y,m_map.bullet_message[i].m_bullet[m_map.bullet_message[i].m_bullet_form]);
    }*/
    int len=m_map.enemy_bullet_message.size();
    for(int i=0;i<len;i++)
    {
        int xx=m_map.enemy_bullet_message[i].m_x-m_map.m_map_up_left_corner_x,yy=m_map.enemy_bullet_message[i].m_y-m_map.m_map_up_left_corner_y;
        painter.drawPixmap(xx+m_map.m_map_corrected_x,yy+m_map.m_map_corrected_y,m_map.enemy_bullet_message[i].m_bullet[m_map.enemy_bullet_message[i].m_bullet_form]);
    }
    //画出英雄
    painter.drawPixmap(960-LEO.m_hero[LEO.m_direction][LEO.m_index].width()/2+m_map.m_map_corrected_x,540-LEO.m_hero[LEO.m_direction][LEO.m_index].height()/2+m_map.m_map_corrected_y,LEO.m_hero[LEO.m_direction][LEO.m_index]);
    //画出护盾
    if(LEO.m_shield)
        painter.drawPixmap(960-m_map.m_shield.width()*0.5+m_map.m_map_corrected_x,540-m_map.m_shield.height()*0.5+m_map.m_map_corrected_y,m_map.m_shield);
    //绘制墙壁
    for(x=(m_map.m_map_up_left_corner_x-m_map.m_map_corrected_x)/MAGNIFICATION;x*MAGNIFICATION<=(m_map.m_map_up_left_corner_x+WINDOW_LENGTH-m_map.m_map_corrected_x);x++){
        for(y=(m_map.m_map_up_left_corner_y-m_map.m_map_corrected_y)/MAGNIFICATION;y*MAGNIFICATION<=(m_map.m_map_up_left_corner_y+WINDOW_WIDTH-m_map.m_map_corrected_y);y++){
            if(m_map.m_map_second[y][x]){
                if(m_map.m_map_second[y-1][x-1]==1&&m_map.m_map_second[y+1][x]==1&&m_map.m_map_second[y][x+1]==1&&m_map.m_map_second[y-1][x]==1&&m_map.m_map_second[y][x-1]==1&&m_map.m_map_second[y+1][x+1]==1&&m_map.m_map_second[y+1][x-1]==1&&m_map.m_map_second[y-1][x+1]==1){
                    //黑墙
                    painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall0[2]);
                }else if(m_map.m_map_second[y+1][x]==0&&m_map.m_map_second[y][x+1]==0&&m_map.m_map_second[y-1][x]==0&&m_map.m_map_second[y][x-1]==0){
                    //独立的墙
                    painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall0[1]);
                }else if(m_map.m_map_second[y-1][x-1]==0&&m_map.m_map_second[y+1][x]==1&&m_map.m_map_second[y][x+1]==1&&m_map.m_map_second[y-1][x]==1&&m_map.m_map_second[y][x-1]==1&&m_map.m_map_second[y+1][x+1]==0&&m_map.m_map_second[y+1][x-1]==0&&m_map.m_map_second[y-1][x+1]==0){
                    //四开的墙
                    painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall0[0]);
                }else if(m_map.m_map_second[y-1][x-1]==0&&m_map.m_map_second[y+1][x]==1&&m_map.m_map_second[y][x+1]==1&&m_map.m_map_second[y-1][x]==0&&m_map.m_map_second[y][x-1]==1&&m_map.m_map_second[y+1][x+1]==1&&m_map.m_map_second[y+1][x-1]==1&&m_map.m_map_second[y-1][x+1]==0){
                    //0 0 0
                    //1 1 1
                    //1 1 1
                    painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall1[2]);
                }
                else if(m_map.m_map_second[y-1][x-1]==1&&m_map.m_map_second[y+1][x]==1&&m_map.m_map_second[y][x+1]==0&&m_map.m_map_second[y-1][x]==1&&m_map.m_map_second[y][x-1]==1&&m_map.m_map_second[y+1][x+1]==0&&m_map.m_map_second[y+1][x-1]==1&&m_map.m_map_second[y-1][x+1]==0){
                    //1 1 0
                    //1 1 0
                    //1 1 0
                    painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall1[1]);
                }
                else if(m_map.m_map_second[y-1][x-1]==1&&m_map.m_map_second[y+1][x]==0&&m_map.m_map_second[y][x+1]==1&&m_map.m_map_second[y-1][x]==1&&m_map.m_map_second[y][x-1]==1&&m_map.m_map_second[y+1][x+1]==0&&m_map.m_map_second[y+1][x-1]==0&&m_map.m_map_second[y-1][x+1]==1){
                    //1 1 1
                    //1 1 1
                    //0 0 0
                    painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall1[3]);
                }else if(m_map.m_map_second[y-1][x-1]==0&&m_map.m_map_second[y+1][x]==1&&m_map.m_map_second[y][x+1]==1&&m_map.m_map_second[y-1][x]==1&&m_map.m_map_second[y][x-1]==0&&m_map.m_map_second[y+1][x+1]==1&&m_map.m_map_second[y+1][x-1]==0&&m_map.m_map_second[y-1][x+1]==1){
                    //0 1 1
                    //0 1 1
                    //0 1 1
                    painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall1[0]);
                }
                else if(m_map.m_map_second[y-1][x]==1&&m_map.m_map_second[y+1][x]==1&&m_map.m_map_second[y][x+1]==0&&m_map.m_map_second[y][x-1]==0){
                    //_ 1 _
                    //0 1 0
                    //_ 1 _

                    //左
                    if(m_map.m_map_second_floor[y][x-1]==1&&m_map.m_map_second_floor[y][x+1]==0)
                        painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall1[0]);
                    //右
                    else if(m_map.m_map_second_floor[y][x-1]==0&&m_map.m_map_second_floor[y][x+1]==1)
                        painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall1[1]);

                    else if(!m_map.m_map_second_floor[y][x+1]&&!m_map.m_map_second_floor[y][x-1]){
                        if(m_map.m_map_second[y][x+4])
                            painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall1[1]);
                        else if(m_map.m_map_second[y][x-4])
                            painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall1[0]);
                    } //单条
                    else painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall8[1]);
                }else if(m_map.m_map_second[y-1][x]==0&&m_map.m_map_second[y+1][x]==0&&m_map.m_map_second[y][x+1]==1&&m_map.m_map_second[y][x-1]==1){
                    //_ 0 _
                    //1 1 1
                    //_ 0 _

                    //下
                    if(m_map.m_map_second_floor[y+1][x]==1&&m_map.m_map_second_floor[y-1][x]==0)
                        painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall1[3]);
                    //上
                    else if(m_map.m_map_second_floor[y+1][x]==0&&m_map.m_map_second_floor[y-1][x]==1)
                        painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall1[2]);
                    else if(!m_map.m_map_second_floor[y+1][x]&&!m_map.m_map_second_floor[y-1][x]){
                        if(m_map.m_map_second[y+4][x])
                            painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall1[3]);
                        else if(m_map.m_map_second[y-4][x])
                            painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall1[2]);
                    }
                    //单条
                    else painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall8[0]);


                }else if(m_map.m_map_second[y-1][x-1]==0&&m_map.m_map_second[y+1][x]==0&&m_map.m_map_second[y][x+1]==1&&m_map.m_map_second[y-1][x]==1&&m_map.m_map_second[y][x-1]==1&&m_map.m_map_second[y+1][x+1]==0&&m_map.m_map_second[y+1][x-1]==0&&m_map.m_map_second[y-1][x+1]==0){
                    //0 1 0
                    //1 1 1
                    //0 0 0

                    //边下
                    if(m_map.m_map_second_floor[y+1][x]==0&&m_map.m_map_second_floor[y-1][x-1]==1)
                        painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall3[2]);
                    //墙
                    else if(m_map.m_map_second_floor[y-1][x+1]==0&&m_map.m_map_second_floor[y-1][x+1]==0){
                        if(m_map.m_map_second[y-1][x-4])
                            painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall6[1]);
                        else if(m_map.m_map_second[y-1][x+4])
                            painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall6[2]);
                    }
                    //边上或内
                    else
                        painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall4[2]);

                }else if(m_map.m_map_second[y-1][x-1]==0&&m_map.m_map_second[y+1][x]==1&&m_map.m_map_second[y][x+1]==0&&m_map.m_map_second[y-1][x]==1&&m_map.m_map_second[y][x-1]==1&&m_map.m_map_second[y+1][x+1]==0&&m_map.m_map_second[y+1][x-1]==0&&m_map.m_map_second[y-1][x+1]==0){
                    //0 1 0
                    //1 1 0
                    //0 1 0

                    //边右
                    if(m_map.m_map_second_floor[y][x+1]==0&&m_map.m_map_second_floor[y-1][x-1]==1)
                        painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall3[0]);
                    //墙
                    else if(m_map.m_map_second_floor[y-1][x-1]==0&&m_map.m_map_second_floor[y+1][x-1]==0){
                        if(m_map.m_map_second[y-4][x-1])
                            painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall6[3]);
                        else if(m_map.m_map_second[y+4][x-1])
                            painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall6[2]);
                    }
                    //边左或内
                    else
                        painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall4[0]);

                }else if(m_map.m_map_second[y-1][x-1]==0&&m_map.m_map_second[y+1][x]==1&&m_map.m_map_second[y][x+1]==1&&m_map.m_map_second[y-1][x]==0&&m_map.m_map_second[y][x-1]==1&&m_map.m_map_second[y+1][x+1]==0&&m_map.m_map_second[y+1][x-1]==0&&m_map.m_map_second[y-1][x+1]==0){
                    //0 0 0
                    //1 1 1
                    //0 1 0

                    //边上
                    if(m_map.m_map_second_floor[y-1][x]==0&&m_map.m_map_second_floor[y+1][x+1]==1)
                        painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall3[3]);
                    //墙
                    else if(m_map.m_map_second_floor[y+1][x-1]==0&&m_map.m_map_second_floor[y+1][x+1]==0){
                        if(m_map.m_map_second[y+1][x-4])
                            painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall6[0]);
                        else if(m_map.m_map_second[y+1][x+4])
                            painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall6[3]);
                    }
                    //边下或内
                    else painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall4[3]);

                }else if(m_map.m_map_second[y-1][x-1]==0&&m_map.m_map_second[y+1][x]==1&&m_map.m_map_second[y][x+1]==1&&m_map.m_map_second[y-1][x]==1&&m_map.m_map_second[y][x-1]==0&&m_map.m_map_second[y+1][x+1]==0&&m_map.m_map_second[y+1][x-1]==0&&m_map.m_map_second[y-1][x+1]==0){
                    //0 1 0
                    //0 1 1
                    //0 1 0
                    //边左
                    if(m_map.m_map_second_floor[y][x-1]==0&&m_map.m_map_second_floor[y+1][x+1]==1)
                        painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall3[1]);
                    //墙
                    else if(m_map.m_map_second_floor[y+1][x+1]==0&&m_map.m_map_second_floor[y-1][x+1]==0){
                        if(m_map.m_map_second[y-4][x+1])
                            painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall6[0]);
                        else if(m_map.m_map_second[y+4][x+1])
                            painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall6[1]);
                    }
                    //边右或内
                    else painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall4[1]);

                }else if(m_map.m_map_second[y-1][x]==0&&m_map.m_map_second[y][x-1]==0&&m_map.m_map_second[y+1][x]==0&&m_map.m_map_second[y][x+1]==1){
                    //_ 0 _
                    //0 1 1
                    //_ 0 _
                    painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall7[0]);
                }
                else if(m_map.m_map_second[y-1][x]==0&&m_map.m_map_second[y][x-1]==1&&m_map.m_map_second[y+1][x]==0&&m_map.m_map_second[y][x+1]==0){
                    //_ 0 _
                    //1 1 0
                    //_ 0 _
                    painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall7[1]);
                }
                else if(m_map.m_map_second[y-1][x]==0&&m_map.m_map_second[y][x-1]==0&&m_map.m_map_second[y+1][x]==1&&m_map.m_map_second[y][x+1]==0){
                    //_ 0 _
                    //0 1 0
                    //_ 1 _
                    painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall7[2]);
                }
                else if(m_map.m_map_second[y-1][x]==1&&m_map.m_map_second[y][x-1]==0&&m_map.m_map_second[y+1][x]==0&&m_map.m_map_second[y][x+1]==0){
                    //_ 1 _
                    //0 1 0
                    //_ 0 _
                    painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall7[3]);
                }
                else if(m_map.m_map_second[y-1][x]==0&&m_map.m_map_second[y][x-1]==0&&m_map.m_map_second[y+1][x]==1&&m_map.m_map_second[y][x+1]==1){
                    //_ 0 _
                    //0 1 1
                    //_ 1 _
                    if(m_map.m_map_second[y+1][x]==1&&m_map.m_map_second[y][x+1]==1&&m_map.m_map_second[y+1][x+1]==1){
                        //_ 0 _
                        //0 1 1
                        //_ 1 1
                        painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall6[0]);

                    }else if(m_map.m_map_second[y+1][x]==1&&m_map.m_map_second[y][x+1]==1&&m_map.m_map_second[y+1][x+1]==0){
                        //_ 0 _
                        //0 1 1
                        //_ 1 0

                        //外
                        if(m_map.m_map_second_floor[y-1][x-1]==0)
                            painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall2[3]);
                        else if(m_map.m_map_second_floor[y+1][x+1]==0&&(m_map.m_map_second_floor[y-1][x]==1||m_map.m_map_second_floor[y][x-1]==1))
                            painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall6[0]);
                        //内

                        else painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall5[0]);

                    }
                    //qDebug()<<"1";
                }else if(m_map.m_map_second[y-1][x]==0&&m_map.m_map_second[y][x+1]==0&&m_map.m_map_second[y+1][x]==1&&m_map.m_map_second[y][x-1]==1){
                    //_ 0 _
                    //1 1 0
                    //_ 1 _
                    if(m_map.m_map_second[y+1][x]==1&&m_map.m_map_second[y][x-1]==1&&m_map.m_map_second[y+1][x-1]==1){
                        //_ 0 _
                        //1 1 0
                        //1 1 _
                        painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall6[3]);

                    }else if(m_map.m_map_second[y+1][x]==1&&m_map.m_map_second[y][x-1]==1&&m_map.m_map_second[y+1][x-1]==0){
                        //_ 0 _
                        //1 1 0
                        //0 1 _

                        //外
                        if(m_map.m_map_second_floor[y-1][x+1]==0)
                            painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall2[2]);
                        else if(m_map.m_map_second_floor[y+1][x-1]==0&&(m_map.m_map_second_floor[y-1][x]==1||m_map.m_map_second_floor[y][x+1]==1))
                            painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall6[3]);
                        //内
                        else painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall5[1]);

                    }
                    //qDebug()<<"2";
                }else if(m_map.m_map_second[y+1][x]==0&&m_map.m_map_second[y][x-1]==0&&m_map.m_map_second[y-1][x]==1&&m_map.m_map_second[y][x+1]==1){

                    //_ 1 _
                    //0 1 1
                    //_ 0 _

                    if(m_map.m_map_second[y-1][x]==1&&m_map.m_map_second[y][x+1]==1&&m_map.m_map_second[y-1][x+1]==1){
                        //_ 1 1
                        //0 1 1
                        //_ 0 _
                        painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall6[1]);

                    }else if(m_map.m_map_second[y-1][x]==1&&m_map.m_map_second[y][x+1]==1&&m_map.m_map_second[y-1][x+1]==0){
                        //_ 1 0
                        //0 1 1
                        //_ 0 _

                        //外
                        if(m_map.m_map_second_floor[y+1][x-1]==0)
                            painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall2[1]);
                        else if(m_map.m_map_second_floor[y-1][x+1]==0&&(m_map.m_map_second_floor[y+1][x]==1||m_map.m_map_second_floor[y][x-1]==1))
                            painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall6[1]);
                        //内
                        else painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall5[2]);

                    }
                    // qDebug()<<"3";
                }else if(m_map.m_map_second[y+1][x]==0&&m_map.m_map_second[y][x+1]==0&&m_map.m_map_second[y-1][x]==1&&m_map.m_map_second[y][x-1]==1){
                    //_ 1 _
                    //1 1 0
                    //_ 0 _

                    if(m_map.m_map_second[y-1][x]==1&&m_map.m_map_second[y][x-1]==1&&m_map.m_map_second[y-1][x-1]==1){
                        //1 1 _
                        //1 1 0
                        //_ 0 _
                        painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall6[2]);

                    }else if(m_map.m_map_second[y-1][x]==1&&m_map.m_map_second[y][x-1]==1&&m_map.m_map_second[y-1][x-1]==0){
                        //0 1 _
                        //1 1 0
                        //_ 0 _

                        //外
                        if(m_map.m_map_second_floor[y+1][x+1]==0)
                            painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall2[0]);
                        else if(m_map.m_map_second_floor[y-1][x-1]==0&&(m_map.m_map_second_floor[y+1][x]==1||m_map.m_map_second_floor[y][x+1]==1))
                            painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall6[2]);
                        //内
                        else painter.drawPixmap(x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall5[3]);
                    }
                    //qDebug()<<"4";
                }

            }
        }
    }
    for(int i_i=0;i_i<m_map.clossed_wall.size();i_i++){
        int x_x=m_map.clossed_wall[i_i].first;
        int y_y=m_map.clossed_wall[i_i].second;
        painter.drawPixmap(x_x*MAGNIFICATION-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,y_y*MAGNIFICATION-m_map.m_map_up_left_corner_y-76+m_map.m_map_corrected_y,m_map.m_map_wall0[1]);
    }

    //绘制敌人
    for(int i_i=0;i_i<m_map.enemy_message.size();i_i++){
        painter.drawPixmap(m_map.enemy_message[i_i].m_x-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,m_map.enemy_message[i_i].m_y-m_map.m_map_up_left_corner_y+m_map.m_map_corrected_y,m_map.enemy_message[i_i].m_enemy);
    }
    //绘制爆炸图片
    len=m_bombs.size();
    //qDebug()<<"A";
    for(int i=0;i<len;i++)
    {
        painter.drawPixmap(m_bombs[i].m_x-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,m_bombs[i].m_y-m_map.m_map_up_left_corner_y+m_map.m_map_corrected_y,m_bombs[i].m_pixarr[m_bombs[i].m_form][m_bombs[i].m_index]);
    }
    //绘制小地图
    //painter.drawPixmap(1600,30,m_map.mini_mapback);
    if(m_map.tab_push){
        painter.setBrush(QBrush(QColor(0,0,0,150)));
        painter.drawRoundRect(960-250,540-250,500,500);
        painter.setBrush(QBrush(QColor(59,59,59)));
        painter.setPen(QPen(QColor(178,178,178),3,Qt::SolidLine,Qt::RoundCap));

        for(int i=0,h=FIRST_ROOM_SIZE/2*(MINI_ROOM_SIZE+MINI_ROOM_INTERVAL)+MINI_ROOM_SIZE/2-150;i<m_map.miniroom_message.size();i++){
            //+m_map.miniroom_left_move_x*(MINI_ROOM_SIZE+MINI_ROOM_INTERVAL)
            //+m_map.miniroom_left_move_y*(MINI_ROOM_SIZE+MINI_ROOM_INTERVAL)

            painter.drawRoundRect(m_map.miniroom_message[i].mini_room_x-h+810,m_map.miniroom_message[i].mini_room_y-h+390,50,50);
            // qDebug()<<"shit";
        }


        for(int i=0,h=FIRST_ROOM_SIZE/2*(MINI_ROOM_SIZE+MINI_ROOM_INTERVAL)+MINI_ROOM_SIZE/2-150;i<m_map.mini_road_message.size();i++){
            //
            //

            painter.drawPixmap(m_map.mini_road_message[i].first-h+810,m_map.mini_road_message[i].second-h+390,m_map.miniroad);
        }
        //painter.setBrush();
        painter.setPen(QPen(QColor(59,59,59),3,Qt::SolidLine,Qt::RoundCap));
        painter.drawRoundRect(935-m_map.miniroom_left_move_x*(MINI_ROOM_SIZE+MINI_ROOM_INTERVAL),515-m_map.miniroom_left_move_y*(MINI_ROOM_SIZE+MINI_ROOM_INTERVAL),50,50);
        painter.setPen(QPen(Qt::gray,3,Qt::DashDotLine,Qt::RoundCap));
        painter.drawRoundRect(935-m_map.miniroom_left_move_x*(MINI_ROOM_SIZE+MINI_ROOM_INTERVAL),515-m_map.miniroom_left_move_y*(MINI_ROOM_SIZE+MINI_ROOM_INTERVAL),50,50);
        // painter.drawPixmap(935-m_map.miniroom_left_move_x*(MINI_ROOM_SIZE+MINI_ROOM_INTERVAL),515-m_map.miniroom_left_move_y*(MINI_ROOM_SIZE+MINI_ROOM_INTERVAL),m_map.miniroom_now);
    }
    //绘制传送门
    //QMatrix matrix;
    //matrix.rotate(m_map.portal_time);
    //aaa.scaled(QSize(216,216),Qt::KeepAspectRatio);
    // QPixmap aaa=m_map.portal_now.portal_1.transformed(matrix,Qt::SmoothTransformation);

    /* painter.drawPixmap(960,540,m_map.portal_now.portal_picture[m_map.portal_now.portal_now_p]);

    if(++m_map.portal_time==10){
    m_map.portal_now.portal_now_p++;
    m_map.portal_now.portal_now_p%=m_map.portal_now.portal_num;
    }
    m_map.portal_time%=10;*/

    //绘制道具
    //统一变化时间
    m_map.props_time+=6;
    for(int i=0;i<m_map.props_message.size();i++){
        painter.drawPixmap(m_map.props_message[i].props_x-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,m_map.props_message[i].props_y-m_map.m_map_up_left_corner_y+m_map.m_map_corrected_y,m_map.props_message[i].props_picture[m_map.props_message[i].picture_now]);
        if(m_map.props_time/100){
            m_map.props_message[i].picture_now++;
            m_map.props_message[i].picture_now%=m_map.props_message[i].picture_num;
        }
    }
    //绘制箱子
    for(int i=0;i<m_map.chests_message.size();i++){
        if(!m_map.chests_message[i].chest_state){
            //未开启
            painter.drawPixmap(m_map.chests_message[i].chest_x-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,m_map.chests_message[i].chest_y-m_map.m_map_up_left_corner_y+m_map.m_map_corrected_y,m_map.chests_message[i].chest_picture[0]);
        }else if(m_map.chests_message[i].chest_state==1){
            //正在开启
            painter.drawPixmap(m_map.chests_message[i].chest_x-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,m_map.chests_message[i].chest_y-m_map.m_map_up_left_corner_y+m_map.m_map_corrected_y,m_map.chests_message[i].chest_picture[m_map.chests_message[i].chest_now]);
            if(m_map.props_time/100)
                m_map.chests_message[i].chest_now++;
            if(m_map.chests_message[i].chest_now==7)
                m_map.chests_message[i].chest_state=2;

        }if(m_map.chests_message[i].chest_state==2){
            painter.drawPixmap(m_map.chests_message[i].chest_x-m_map.m_map_up_left_corner_x+m_map.m_map_corrected_x,m_map.chests_message[i].chest_y-m_map.m_map_up_left_corner_y+m_map.m_map_corrected_y,m_map.chests_message[i].chest_picture[6]);
        }
    }
    m_map.props_time%=100;


    //绘制小地图

    painter.setBrush(QBrush(QColor(0,0,0,150)));
    painter.drawRoundRect(1600,30,300,300);
    QPen m_pen;
    m_pen.setWidth(1);
    m_pen.setColor(Qt::white);
    //painter.setPen(QPen(Qt::white),1);
    painter.setPen(m_pen);
    painter.setBrush(Qt::white);
    x=(m_map.m_map_up_left_corner_x+WINDOW_LENGTH/2)/MAGNIFICATION-28;
    y=(m_map.m_map_up_left_corner_y+WINDOW_WIDTH/2)/MAGNIFICATION-21;
    int x_x=x;
    int y_y=y;
    //m_map.miniroom_message.clear();
    for(;x_x<=(x+56);x_x++){
        for(y_y=(m_map.m_map_up_left_corner_y-WINDOW_WIDTH)/MAGNIFICATION;y_y<=(y+56);y_y++){
            if(m_map.m_map_second[y_y][x_x]){

                if(m_map.room_message[m_map.m_map_first_identifier[y_y/(MAX_ROOM_SIZE+ROAD_LENGTH)][x_x/(MAX_ROOM_SIZE+ROAD_LENGTH)]-1].room_end==0){
                    /*int it=m_map.room_message[m_map.m_map_first_identifier[y_y/(MAX_ROOM_SIZE+ROAD_LENGTH)][x_x/(MAX_ROOM_SIZE+ROAD_LENGTH)]-1].room_identier;
                      int tag=0;
for(int i_i=0;i_i<m_map.miniroom_message.size();i_i++){
    if(m_map.miniroom_message[i_i].mini_room_identier==it)
        tag=1;
}
if(!tag){
    miniroom a;
    qDebug()<<it;
    a.mini_room_x=m_map.room_message[it-1].max_up_left_corner_x;
    a.mini_room_y=m_map.room_message[it-1].max_up_left_corner_y;
a.mini_room_identier=it;
m_map.miniroom_message.append(a);
}*/
                    continue;
                }

                painter.drawRect(1605+(x_x-x)*5,35+(y_y-y)*5,5,5);//qDebug()<<"sda";
            }

        }
    }
    /*painter.setBrush(Qt::gray);
   for(int i_i=0;i_i<m_map.miniroom_message.size();i_i++){
       painter.drawRect(1605+(m_map.miniroom_message[i_i].mini_room_x-x)*5,35+(m_map.miniroom_message[i_i].mini_room_y-y)*5,195,195);
   }*/

    // painter.drawPixmap(960,540,m_map.m_map_wall2[0]);
    //英雄血量
    for(int i=0;i<(LEO.m_hp>>1);i++)
        painter.drawPixmap(i*80,0,m_map.blood_max);
    int ii=(LEO.m_hp>>1);
    if(LEO.m_hp&1)
    {
        painter.drawPixmap(ii*80,0,m_map.blood_mid);
        ii++;
    }
    for(int i=ii;i<LEO.m_hp_limit;i++)
        painter.drawPixmap(i*80,0,m_map.blood_empty);
    int ttx=(LEO.m_shield>>1);
    for(int i=0;i<ttx;i++)
        painter.drawPixmap((LEO.m_hp_limit+i)*80,0,m_map.m_shield_max);
    if(LEO.m_shield&1)
        painter.drawPixmap((LEO.m_hp_limit+ttx)*80,0,m_map.m_shield_mid);



}

void mainscene::keyPressEvent(QKeyEvent *event)
{

    switch(event->key()){
    case Qt::Key_W:
    {
        m_map.now_move_w=1;
        break;
    }
    case Qt::Key_A:
    {
        m_map.now_move_a=1;
        break;
    }
    case Qt::Key_S:
    {
        m_map.now_move_s=1;
        break;
    }
    case Qt::Key_D:
    {
        m_map.now_move_d=1;
        break;
    }
    case Qt::Key_Tab:
    {
        m_map.tab_push^=1;
        break;
    }
    case Qt::Key_K:
    {
        m_map.enemy_message.clear();
        break;
    }
    case Qt::Key_Escape:
    {
        m_map.is_pause^=1;
        //m_map.tab_push^=1;
        if(m_map.is_pause)
            m_timer.stop();
        else m_timer.start();
        break;
    }
    case Qt::Key_F:
    {
        for(int ii=0;ii<m_map.chests_message.size();ii++){

            if(m_map.chests_message[ii].chest_rect.intersects(LEO.m_rect)){
                if(m_map.chests_message[ii].chest_state==0)
                    m_map.chests_message[ii].chest_state=1;}
        }
        break;
    }
    default:
        break;
    }
}

void mainscene::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_W:
    {
        m_map.now_move_w=0;
        break;
    }
    case Qt::Key_A:
    {
        m_map.now_move_a=0;
        break;
    }
    case Qt::Key_S:
    {
        m_map.now_move_s=0;
        break;
    }
    case Qt::Key_D:
    {
        m_map.now_move_d=0;
        break;
    }
    default:
        break;
    }
}
void mainscene::mousePressEvent(QMouseEvent *event)
{

    if(event->button()==Qt::LeftButton)
    {
        m_map.now_shooting=1;
    }
    if(event->button()==Qt::RightButton)
    {
        LEO.m_weapon_index=LEO.m_weapon_index<LEO.now_weapon_num?(LEO.m_weapon_index+1):1;
    }

}
void mainscene::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        m_map.now_shooting=0;
    }
}

void mainscene::SceneChange()
{
    QPoint a_a = QCursor::pos();
    int x=(a_a.x()-960)/2;
    int y=(a_a.y()-540)/2;
    m_map.m_map_corrected_x=-x;
    m_map.m_map_corrected_y=-y;
}

void mainscene::Play_Game()
{
    m_timer.start();
    connect(&m_timer,&QTimer::timeout,[=](){
        SceneChange();
        Hero_Move();
        Shooting();
        Moving();
        Updata_AllMessage();
        collisionDetection();
        Bomb_UpdatePosition();

        Bullet_UpdatePosition();
        update();
        Update_Deathmessage();
    });
}
void mainscene::CreateBullet(double k,int dx,int dy,int flag,int cur,int bullet_form,int speed)
{
    //创建子弹
    bullet temp;
    temp.speed=speed;
    //子弹类型
    temp.m_bullet_form=bullet_form;
    if(flag)
    {//英雄子弹坐标
        temp.m_x=960-temp.m_bullet[bullet_form].width()*0.5+m_map.m_map_up_left_corner_x;
        temp.m_y=540-temp.m_bullet[bullet_form].height()*0.5+m_map.m_map_up_left_corner_y;
    }
    else
    {
        //怪物子弹坐标
        temp.m_x=m_map.enemy_message[cur].m_x+m_map.enemy_message[cur].m_enemy.width()*0.5-temp.m_bullet[bullet_form].width()*0.5;
        temp.m_y=m_map.enemy_message[cur].m_y+m_map.enemy_message[cur].m_enemy.height()*0.5-temp.m_bullet[bullet_form].height()*0.5;
    }
    //子弹方向
    temp.dy=dy;
    temp.dx=dx;
    temp.direction=k;
    //子弹矩形框
    temp.m_rect.setWidth(temp.m_bullet[bullet_form].width());
    temp.m_rect.setHeight(temp.m_bullet[bullet_form].height());
    temp.m_rect.moveTo(temp.m_x,temp.m_y);
    if(flag)
        m_map.bullet_message.push_back(temp);
    else
        m_map.enemy_bullet_message.push_back(temp);
}
void mainscene::InitHeroPosition()
{
    //英雄坐标
    LEO.m_x=m_map.m_map_up_left_corner_x+960-LEO.m_hero[LEO.m_direction][LEO.m_index].width()*0.5;
    LEO.m_y=m_map.m_map_up_left_corner_y+540-LEO.m_hero[LEO.m_direction][LEO.m_index].height()*0.5;
    //英雄矩形框
    LEO.m_rect.setWidth(LEO.m_hero[LEO.m_direction][LEO.m_index].width());
    LEO.m_rect.setHeight(LEO.m_hero[LEO.m_direction][LEO.m_index].height());
    //英雄位置
    LEO.m_rect.moveTo(LEO.m_x,LEO.m_y);

}
void mainscene::Hero_Move()
{
    //英雄坐标
    LEO.m_x=m_map.m_map_up_left_corner_x+960-LEO.m_hero[LEO.m_direction][LEO.m_index].width()*0.5;
    LEO.m_y=m_map.m_map_up_left_corner_y+540-LEO.m_hero[LEO.m_direction][LEO.m_index].height()*0.5;
    //英雄矩形框
    LEO.m_rect.setWidth(LEO.m_hero[LEO.m_direction][LEO.m_index].width());
    LEO.m_rect.setHeight(LEO.m_hero[LEO.m_direction][LEO.m_index].height());
    //英雄位置
    LEO.m_rect.moveTo(LEO.m_x,LEO.m_y);

}
void mainscene::Bullet_UpdatePosition()
{
    //现有子弹数目
    int len=m_map.bullet_message.size();
    for(int i=0;i<len;i++)
    {
        double s=m_map.bullet_message[i].speed;
        if(m_map.bullet_message[i].dx!=0)
        {
            double k=m_map.bullet_message[i].direction;
            double dtx=sqrt(s*s/(k*k+1))*m_map.bullet_message[i].dx;
            double dty=sqrt(s*s*k*k/(k*k+1))*m_map.bullet_message[i].dy;
            m_map.bullet_message[i].m_x+=dtx;
            m_map.bullet_message[i].m_y+=dty;
            int x=m_map.bullet_message[i].m_x,y=m_map.bullet_message[i].m_y;
            m_map.bullet_message[i].m_rect.moveTo(x,y);
        }
        else
        {
            m_map.bullet_message[i].m_y+=m_map.bullet_message[i].dy*s;
            int x=m_map.bullet_message[i].m_x,y=m_map.bullet_message[i].m_y;
            m_map.bullet_message[i].m_rect.moveTo(x,y);
        }
    }
    len=m_map.enemy_bullet_message.size();
    for(int i=0;i<len;i++)
    {
        double s=m_map.enemy_bullet_message[i].speed;
        if(m_map.enemy_bullet_message[i].dx!=0)
        {
            double k=m_map.enemy_bullet_message[i].direction;
            double dtx=sqrt(s*s/(k*k+1))*m_map.enemy_bullet_message[i].dx;
            double dty=sqrt(s*s*k*k/(k*k+1))*m_map.enemy_bullet_message[i].dy;
            m_map.enemy_bullet_message[i].m_x+=dtx;
            m_map.enemy_bullet_message[i].m_y+=dty;
            int x=m_map.enemy_bullet_message[i].m_x,y=m_map.enemy_bullet_message[i].m_y;
            m_map.enemy_bullet_message[i].m_rect.moveTo(x,y);
        }
        else
        {
            m_map.enemy_bullet_message[i].m_y+=m_map.enemy_bullet_message[i].dy*s;
            int x=m_map.enemy_bullet_message[i].m_x,y=m_map.enemy_bullet_message[i].m_y;
            m_map.enemy_bullet_message[i].m_rect.moveTo(x,y);
        }
    }
}
void mainscene::collisionDetection()
{
    //英雄子弹碰撞检测
    int num=m_map.bullet_message.size();
    for(int i=0;i<num;i++)
    {
        //碰到墙壁，消失
        int form=m_map.bullet_message[i].m_bullet_form;
        int h=m_map.bullet_message[i].m_bullet[form].height();
        int w=m_map.bullet_message[i].m_bullet[form].width();
        //四点判是否碰撞
        int x1=m_map.bullet_message[i].m_x/MAGNIFICATION,y1=m_map.bullet_message[i].m_y/MAGNIFICATION;
        int x2=(m_map.bullet_message[i].m_x+w)/MAGNIFICATION,y2=y1;
        int x3=x1,y3=(m_map.bullet_message[i].m_y+h)/MAGNIFICATION;
        int x4=x2,y4=y3;
        if(m_map.m_map_second[y1][x1]||m_map.m_map_second[y4][x4]||m_map.m_map_second[y2][x2]||m_map.m_map_second[y3][x3])
        {
            //播放爆炸效果
            Create_Bomb(m_map.bullet_message[i].m_x,m_map.bullet_message[i].m_y,m_map.bullet_message[i].m_bullet_form);
            m_map.bullet_message.remove(i);
            num--;
            i--;
        }
        else
        {
            for(int j=0;j<m_map.enemy_message.size();j++){
                if(m_map.bullet_message[i].m_rect.intersects(m_map.enemy_message[j].m_rect))
                {
                    m_map.enemy_message[j].hp-=arsenal.attack[LEO.m_weapon[LEO.m_weapon_index]];
                    int xx=m_map.enemy_message[j].m_x+m_map.enemy_message[j].m_enemy.width()*0.5;
                    int yy=m_map.enemy_message[j].m_y+m_map.enemy_message[j].m_enemy.height()*0.5;
                    //播放爆炸效果
                    Create_Bomb(xx,yy,m_map.bullet_message[i].m_bullet_form);
                    if(m_map.enemy_message[j].hp<=0){
                        //掉落道具
                        props a_a;
                        a_a.Enemy_died_Props_init();
                        //
                        a_a.props_x=m_map.enemy_message[j].m_x;
                        a_a.props_y=m_map.enemy_message[j].m_y;


                        //死亡后宝箱生成
                        //qDebug()<<m_map.enemy_message.size();
                        if(m_map.enemy_message.size()==1){
                            //qDebug()<<"shit";
                            chest chest_temp;
                            chest_temp.chest_x=m_map.enemy_message[j].m_x;
                            chest_temp.chest_y=m_map.enemy_message[j].m_y;
                            // qDebug()<<"enemyxy";
                            //  qDebug()<<m_map.enemy_message[j].m_x;
                            // qDebug()<<m_map.enemy_message[j].m_y;
                            chest_temp.chest_rect.setRect(m_map.enemy_message[j].m_x+12,m_map.enemy_message[j].m_y+36,64,56);
                            m_map.chests_message.append(chest_temp);
                        }
                        m_map.props_message.append(a_a);
                        m_map.enemy_message.remove(j);
                    }
                    m_map.bullet_message.remove(i);
                    i--;
                    num--;
                    break;
                }
            }
        }
    }
    //怪物子弹碰撞检测
    num=m_map.enemy_bullet_message.size();
    for(int i=0;i<num;i++)
    {
        //打中英雄
        if(m_map.enemy_bullet_message[i].m_rect.intersects(LEO.m_rect))
        {
            if(LEO.m_shield)
                LEO.m_shield-=1;
            else
                LEO.m_hp-=1;
            //播放爆炸效果
            int xx=960+m_map.m_map_up_left_corner_x,yy=540+m_map.m_map_up_left_corner_y;
            Create_Bomb(xx,yy,2);
            m_map.enemy_bullet_message.remove(i);
            num--;
            i--;
            continue;
        }
        //碰到墙壁，消失
        int form=m_map.enemy_bullet_message[i].m_bullet_form;
        int w=m_map.enemy_bullet_message[i].m_bullet[form].width(),h=m_map.enemy_bullet_message[i].m_bullet[form].height();
        int x1=m_map.enemy_bullet_message[i].m_x/MAGNIFICATION,y1=m_map.enemy_bullet_message[i].m_y/MAGNIFICATION;
        int x2=(m_map.enemy_bullet_message[i].m_x+w)/MAGNIFICATION,y2=y1;
        int x3=x1,y3=(m_map.enemy_bullet_message[i].m_y+h)/MAGNIFICATION;
        int x4=x2,y4=y3;
        if(m_map.m_map_second[y1][x1]||m_map.m_map_second[y4][x4]||m_map.m_map_second[y2][x2]||m_map.m_map_second[y3][x3])
        {
            //播放爆炸效果
            Create_Bomb(m_map.enemy_bullet_message[i].m_x,m_map.enemy_bullet_message[i].m_y,2);
            m_map.enemy_bullet_message.remove(i);
            num--;
            i--;
        }

    }
}
void mainscene::Create_Bomb(int x,int y,int k)
{
    bomb temp;
    temp.m_x=x;
    temp.m_y=y;
    temp.m_form=k;
    m_bombs.push_back(temp);
}
void mainscene::Room_Start_Init(int room_n)
{

    //关闭墙壁
    m_map.Room_Close(room_n);

    room a_a=m_map.room_message[room_n-1];
    //向map中载入敌人信息

    for(int i_i=0;i_i<a_a.room_enemy_message.size();i_i++)
        m_map.enemy_message.append(a_a.room_enemy_message[i_i]);
    m_map.room_message[room_n-1].room_end=1;
    Add_Miniroom(room_n);

}

void mainscene::Updata_AllMessage()
{
    //判断当前所处房间位置
    int room_n=m_map.Room_Judge();
    if(room_n){


        if(room_n!=m_map.room_last_time){
            if(!m_map.room_last_time){
                Add_Miniroom(room_n);
                m_map.room_last_time=room_n;

            }
            else{

                int x=m_map.room_message[room_n-1].center_x/(MAX_ROOM_SIZE+ROAD_LENGTH);
                int y=m_map.room_message[room_n-1].center_y/(MAX_ROOM_SIZE+ROAD_LENGTH);
                for(int i=0;i<4;i++){
                    if(m_map.m_map_first_identifier[y+m_map.m_map_first_direction[1][i]][x+m_map.m_map_first_direction[0][i]]==m_map.room_last_time){
                        m_map.miniroom_left_move_x+=m_map.m_map_first_direction[0][i];
                        m_map.miniroom_left_move_y+=m_map.m_map_first_direction[1][i];
                        //llllllllllllllllllllllllllll
                        int tag=0;
                        for(int i_i=0;i_i<m_map.mini_room_connect.size();i_i++)
                        {
                            if(m_map.mini_room_connect[i_i].first==room_n&&m_map.mini_room_connect[i_i].first==m_map.room_last_time)
                                tag=1;
                            if(m_map.mini_room_connect[i_i].first==m_map.room_last_time&&m_map.mini_room_connect[i_i].first==room_n)
                                tag=1;
                        }
                        if(!tag){
                            int x_x=x*(MINI_ROOM_SIZE+MINI_ROOM_INTERVAL);
                            int y_y=y*(MINI_ROOM_SIZE+MINI_ROOM_INTERVAL);
                            //first x,second y;
                            if(i==0)
                                m_map.mini_road_message.append({x_x+MINI_ROOM_SIZE,y_y+MINI_ROOM_SIZE/2-MINI_ROOM_INTERVAL/2});
                            else if(i==1)
                                m_map.mini_road_message.append({x_x+MINI_ROOM_SIZE/2-MINI_ROOM_INTERVAL/2,y_y-MINI_ROOM_INTERVAL});
                            else if(i==2)
                                m_map.mini_road_message.append({x_x-MINI_ROOM_INTERVAL,y_y+MINI_ROOM_SIZE/2-MINI_ROOM_INTERVAL/2});
                            else m_map.mini_road_message.append({x_x+MINI_ROOM_SIZE/2-MINI_ROOM_INTERVAL/2,y_y+MINI_ROOM_SIZE});
                            m_map.mini_room_connect.append({m_map.room_last_time,room_n});
                        }
                    }
                }
            }m_map.room_last_time=room_n;



        }
        //如果所处房间未开始则载入房间信息并进行初始化
        if(!m_map.room_message[room_n-1].room_end)
            Room_Start_Init(room_n);
        //如果所处房间正在进行中，判断是否结束并更新
        else if(m_map.room_message[room_n-1].room_end==1){

            if(m_map.enemy_message.isEmpty()){
                m_map.room_message[room_n-1].room_end=2;
                m_map.Room_Open();

            }

        }
    }
    //小怪的随机移动和自卫范围内追击和射击
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0;i<m_map.enemy_message.size();i++)
    {
        m_map.enemy_message[i].time++;
        double y=m_map.enemy_message[i].m_y+m_map.enemy_message[i].m_enemy.height()*0.5-LEO.m_y-LEO.m_hero[LEO.m_direction][LEO.m_index].height()*0.5;
        double x=m_map.enemy_message[i].m_x+m_map.enemy_message[i].m_enemy.width()*0.5-LEO.m_x-LEO.m_hero[LEO.m_direction][LEO.m_index].width()*0.5;
        if(x*x+y*y<=SELF_DEFENSE)
        {
            int dx=1,dy=1;
            if(x>0)
                dx=-1;
            else if(x<0.01&&x>=0)
                dx=0;
            if(y>0)
                dy=-1;
            else if(y<0.01&&y>=0)
                dy=0;
            double k=1.0*y/x;
            double s=ENEMY_SPEED;
            double dtx=sqrt(s*s/(k*k+1))*dx;
            double dty=sqrt(s*s*k*k/(k*k+1))*dy;
            m_map.enemy_message[i].m_x+=dtx;
            m_map.enemy_message[i].m_y+=dty;
            int cx=m_map.enemy_message[i].m_enemy.width(),cy=m_map.enemy_message[i].m_enemy.height();
            int tcx1=m_map.enemy_message[i].m_x/MAGNIFICATION,tcy1=m_map.enemy_message[i].m_y/MAGNIFICATION;
            int tcx2=(m_map.enemy_message[i].m_x+cx)/MAGNIFICATION,tcy2=(m_map.enemy_message[i].m_y)/MAGNIFICATION;
            int tcx3=tcx1,tcy3=(m_map.enemy_message[i].m_x+cy)/MAGNIFICATION;
            int tcx4=tcx2,tcy4=tcy3;
            if(m_map.m_map_second[tcy1][tcx1]||m_map.m_map_second[tcy2][tcx2]||m_map.m_map_second[tcy3][tcx3]||m_map.m_map_second[tcy4][tcx4])
            {
                m_map.enemy_message[i].m_x-=dtx;
                m_map.enemy_message[i].m_y-=dty;
            }
            if(m_map.enemy_message[i].enemy_type==1)
            {
                if(m_map.enemy_message[i].time>=ENEMY_STRAIGHT_SHOOTING_INTERVAL)
                {
                    m_map.enemy_message[i].time=0;
                    CreateBullet(k,dx,dy,0,i,1,ENEMY_STRAIGHT_BULLET_SPEED);
                }
            }
            else if(m_map.enemy_message[i].enemy_type==2){
                if(m_map.enemy_message[i].time>=ENEMY_CIRCLE_SHOOTING_INTERVAL)
                {
                    double dx,dy,k;
                    k=tan(m_map.enemy_message[i].degree[m_map.enemy_message[i].m_index]*1.0*acos(-1)/180);
                    m_map.enemy_message[i].time=0;
                    if(m_map.enemy_message[i].degree[m_map.enemy_message[i].m_index]<90&&m_map.enemy_message[i].degree[m_map.enemy_message[i].m_index]>0)
                    {
                        dx=1;
                        dy=-1;
                    }
                    else if(m_map.enemy_message[i].degree[m_map.enemy_message[i].m_index]<180&&m_map.enemy_message[i].degree[m_map.enemy_message[i].m_index]>90){
                        dx=-1;
                        dy=-1;
                    }
                    else if(m_map.enemy_message[i].degree[m_map.enemy_message[i].m_index]<270&&m_map.enemy_message[i].degree[m_map.enemy_message[i].m_index]>180){
                        dx=-1;
                        dy=1;
                    }
                    else if(m_map.enemy_message[i].degree[m_map.enemy_message[i].m_index]<360&&m_map.enemy_message[i].degree[m_map.enemy_message[i].m_index]>270){
                        dx=1;
                        dy=1;
                    }
                    else if(m_map.enemy_message[i].degree[m_map.enemy_message[i].m_index]==0)
                    {
                        dy=0,dx=1;
                    }
                    else if(m_map.enemy_message[i].degree[m_map.enemy_message[i].m_index]==90)
                    {
                        dy=-1,dx=0;
                    }
                    else if(m_map.enemy_message[i].degree[m_map.enemy_message[i].m_index]==180)
                    {
                        dy=0,dx=-1;
                    }
                    else
                    {
                        dy=1,dx=0;
                    }
                    CreateBullet(k,dx,dy,0,i,1,ENEMY_CIRCLE_BULLET_SPEED);
                    m_map.enemy_message[i].m_index=m_map.enemy_message[i].m_index<11?(m_map.enemy_message[i].m_index+1):0;
                }
            }
            int x=m_map.enemy_message[i].m_x,y=m_map.enemy_message[i].m_y;
            m_map.enemy_message[i].m_rect.moveTo(x,y);
        }
        else
        {
            int dx[4]={0,ENEMY_SPEED,-ENEMY_SPEED,0},dy[4]={ENEMY_SPEED,0,0,-ENEMY_SPEED};
            int x=qrand()%4;
            m_map.enemy_message[i].m_x+=dx[x];
            m_map.enemy_message[i].m_y+=dy[x];
            int cx=m_map.enemy_message[i].m_enemy.width(),cy=m_map.enemy_message[i].m_enemy.height();
            int tcx1=m_map.enemy_message[i].m_x/MAGNIFICATION,tcy1=m_map.enemy_message[i].m_y/MAGNIFICATION;
            int tcx2=(m_map.enemy_message[i].m_x+cx)/MAGNIFICATION,tcy2=(m_map.enemy_message[i].m_y)/MAGNIFICATION;
            int tcx3=tcx1,tcy3=(m_map.enemy_message[i].m_x+cy)/MAGNIFICATION;
            int tcx4=tcx2,tcy4=tcy3;
            if(m_map.m_map_second[tcy1][tcx1]||m_map.m_map_second[tcy2][tcx2]||m_map.m_map_second[tcy3][tcx3]||m_map.m_map_second[tcy4][tcx4])
            {
                m_map.enemy_message[i].m_x-=dx[x];
                m_map.enemy_message[i].m_y-=dy[x];
            }
            m_map.enemy_message[i].m_rect.moveTo(m_map.enemy_message[i].m_x, m_map.enemy_message[i].m_y);
        }
    }
}

void mainscene::Add_Miniroom(int room_n)
{
    miniroom a;
    a.mini_room_identier=room_n;
    a.mini_room_x=(m_map.m_map_up_left_corner_x+WINDOW_LENGTH/2)/MAGNIFICATION/(MAX_ROOM_SIZE+ROAD_LENGTH)*(MINI_ROOM_SIZE+MINI_ROOM_INTERVAL);
    a.mini_room_y=(m_map.m_map_up_left_corner_y+WINDOW_LENGTH/2)/MAGNIFICATION/(MAX_ROOM_SIZE+ROAD_LENGTH)*(MINI_ROOM_SIZE+MINI_ROOM_INTERVAL);
    m_map.miniroom_message.append(a);
}

void mainscene::Shooting()
{if(m_map.now_shooting){
        //控制射速
        int t_time=1000/5;//每秒射5发
        if(((m_map.shooting_time+GAME_RATE)/t_time-m_map.shooting_time/t_time)==1){
            QPoint a= QWidget::mapFromGlobal(QCursor::pos());
            if(LEO.m_weapon_index==2)
            {
                double x=a.x(),y=a.y();
                double k=(y-540)/(x-960);
                double r=sqrt((y-540)*(y-540)+(x-960)*(x-960));
                for(int i=0;i<3;i++)
                {
                    int dx,dy;
                    double x1,y1;
                    double degree=atan(k);
                    if(i==0)
                    {
                        x1=x;
                        y1=y;
                    }
                    else if(i==1)
                    {
                        degree+=atan(tan(15*acos(-1)/180));
                    }
                    else if(i==2)
                    {
                        degree-=atan(tan(15*acos(-1)/180));
                    }
                    if(k>0)
                    {
                        if(x<960)
                            degree+=acos(-1);
                        x1=960+r*cos(degree);
                        y1=540+r*sin(degree);
                    }
                    else
                    {
                        if(x<960)
                            degree+=acos(-1);
                        x1=960+r*cos(degree);
                        y1=540+r*sin(degree);
                    }
                    double k=(y1-540)/(x1-960);
                    if(x1>960)
                        dx=1;
                    else if(x1<960)
                        dx=-1;
                    else
                        dx=0;
                    if(y1>540)
                        dy=1;
                    else
                        dy=-1;
                    CreateBullet(k,dx,dy,1,0,LEO.m_weapon[LEO.m_weapon_index],HERO_BULLET_SPEED);
                }
            }
            else
            {
                double x=a.x(),y=a.y();
                int dx,dy;
                if(x>960)
                    dx=1;
                else if(x<960)
                    dx=-1;
                else
                    dx=0;
                if(y>540)
                    dy=1;
                else
                    dy=-1;
                //斜率
                //异常处理
                try{
                  double k=division(y-540,x-960);
                   CreateBullet(k,dx,dy,1,0,LEO.m_weapon[LEO.m_weapon_index],HERO_BULLET_SPEED);
                }
                catch (const char* msg) {
                    qDebug()<< msg << endl;
                 }
            }
            m_map.shooting_time=(m_map.shooting_time+GAME_RATE)%t_time;
        }
        else m_map.shooting_time+=GAME_RATE;
    }
}

void mainscene::Moving()
{

    if(m_map.now_move_w)
    {
        if(LEO.m_direction!=1)
        {
            LEO.m_direction=1;
            LEO.m_index=0;
            LEO.m_recoder=0;
        }
        LEO.Hero_UpdateInfo();
        m_map.m_map_up_left_corner_y-=MOVE_SPEED;
        int y=m_map.m_map_up_left_corner_y+540+LEO.m_hero[LEO.m_direction][LEO.m_index].height()*0.5;
        int x=m_map.m_map_up_left_corner_x+960;
        y/=MAGNIFICATION;
        x/=MAGNIFICATION;
        if(m_map.m_map_second[y][x])
        {
            m_map.m_map_up_left_corner_y+=MOVE_SPEED;
        }

    }
    if(m_map.now_move_a)
    {
        if(LEO.m_direction!=3)
        {
            LEO.m_direction=3;
            LEO.m_index=0;
            LEO.m_recoder=0;
        }
        LEO.Hero_UpdateInfo();
        m_map.m_map_up_left_corner_x-=MOVE_SPEED;
        int y=m_map.m_map_up_left_corner_y+540+LEO.m_hero[LEO.m_direction][LEO.m_index].height()*0.5;
        int x=m_map.m_map_up_left_corner_x+960;
        y/=MAGNIFICATION;
        x/=MAGNIFICATION;
        if(m_map.m_map_second[y][x])
        {
            m_map.m_map_up_left_corner_x+=MOVE_SPEED;
        }

    }
    if(m_map.now_move_s)
    {
        if(LEO.m_direction!=2)
        {
            LEO.m_direction=2;
            LEO.m_index=0;
            LEO.m_recoder=0;
        }
        LEO.Hero_UpdateInfo();
        m_map.m_map_up_left_corner_y+=MOVE_SPEED;
        int y=m_map.m_map_up_left_corner_y+540+LEO.m_hero[LEO.m_direction][LEO.m_index].height()*0.5;
        int x=m_map.m_map_up_left_corner_x+960;
        y/=MAGNIFICATION;
        x/=MAGNIFICATION;
        if(m_map.m_map_second[y][x])
        {
            m_map.m_map_up_left_corner_y-=MOVE_SPEED;
        }

    }
    if(m_map.now_move_d)
    {
        if(LEO.m_direction!=4)
        {
            LEO.m_direction=4;
            LEO.m_index=0;
            LEO.m_recoder=0;
        }
        LEO.Hero_UpdateInfo();
        m_map.m_map_up_left_corner_x+=MOVE_SPEED;
        int y=m_map.m_map_up_left_corner_y+540+LEO.m_hero[LEO.m_direction][LEO.m_index].height()*0.5;
        int x=m_map.m_map_up_left_corner_x+960;
        y/=MAGNIFICATION;
        x/=MAGNIFICATION;
        if(m_map.m_map_second[y][x])
        {
            m_map.m_map_up_left_corner_x-=MOVE_SPEED;
        }
    }

}
void mainscene::Update_Deathmessage()
{
    //游戏失败
    if(!LEO.m_hp)
    {
        m_timer.stop();
        QLabel *loseLable = new QLabel;
        QPixmap tmpPix;
        tmpPix.load(":/source/lose.png");
        loseLable->setGeometry(0,0,tmpPix.width(),tmpPix.height());
        loseLable->setPixmap(tmpPix);
        loseLable->setParent(this);
        loseLable->move((this->width() - tmpPix.width())*0.5,-tmpPix.height());
        loseLable->show();

        QWidget *widget=new QWidget(this,Qt::FramelessWindowHint);
        widget->resize(this->size());
        widget->setObjectName("widget");
        widget->setStyleSheet("#widget{background-color:rgba(10,10,10,100);}");
        widget->show();
        //将失败图片砸下
        QPropertyAnimation *animation = new QPropertyAnimation(loseLable,"geometry");
        //时间间隔
        animation->setDuration(1000);
        //开始位置
        animation->setStartValue(QRect(loseLable->x(),loseLable->y(),loseLable->width(),loseLable->height()));
        //结束位置
        animation->setEndValue(QRect(loseLable->x(),248,loseLable->width(),loseLable->height()));
        //缓和曲线
        animation->setEasingCurve(QEasingCurve::OutBounce);
        animation->start();

        mtimer= new QTimer(this);
        mtimer->setSingleShot(true);
        this->Qtimer();
        connect(mtimer,&QTimer::timeout,this,[=](){emit show_deathpage();});
        deathpage* transmit = new deathpage();
       QObject::connect(this,SIGNAL(show_deathpage()),transmit,SLOT(show_page()));
        connect(mtimer,&QTimer::timeout,this,[=](){emit close_mainscene();});
        connect(this,&mainscene::close_mainscene,this,&mainscene::close_page);

    }
}
void mainscene::Qtimer()//计时
{
    mtimer->start(2000);
}
void mainscene::close_page()//死亡页面
{
    this->close();
}
void mainscene::open_page()
{
    this->show();
}

