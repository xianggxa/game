#ifndef BULLET_H
#define BULLET_H
#include"config.h"
#include<QPixmap>
class bullet
{
public:
    bullet();
public:
    //子弹资源对象
    QPixmap m_bullet[10];
    double direction;
    //子弹坐标
    int dx,dy;
    double speed;
    double m_x;
    double m_y;
    //子弹的矩形边框（用于碰撞检测）
    QRect m_rect;
    int m_bullet_form;
    int m_shooting_form;
};

#endif // BULLET_H
