#ifndef ENEMY_H
#define ENEMY_H
#include "QPixmap"
#include "QRect"
class enemy
{
public:
    enemy();
public:
    //血量
    int hp;
    //伤害
    int attack;
    //初始位置
    int enemy_left_coner_x;
    int enemy_left_coner_y;
    double m_x;
    double m_y;
    //贴图
    QPixmap m_enemy;
    //碰撞框
    QRect m_rect;
    //小兵种类
    int enemy_type;
    //圆射角度
    int degree[15];
    //选择圆射角度位置
    int m_index;
    int time;
};

#endif // ENEMY_H
