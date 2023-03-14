#ifndef HERO_H
#define HERO_H
#include<QString>
#include<QPixmap>
#include "config.h"
class hero
{
public:
    hero();
    //更新信息（播放图片下标、播放间隔）
    void Hero_UpdateInfo();
public:
    //角色等级
    int m_level;
    //角色血量
    int m_hp_limit;
    int m_hp;
    //当前武器
    int m_weapon_index;
    int m_weapon[3];
    int now_weapon_num;
    //角色经验
    int m_experience;
    //行走状态图片
    QVector<QPixmap>m_hero[5];
    //当前行走方向，1为上，2为下，3为左，4为右
    int m_direction;
    //移动切图的时间间隔
    int m_recoder;
    //移动时加载的图片下标
    int m_index;
    //英雄坐标
    int m_x;
    int m_y;
    //英雄的矩形边框（用于碰撞检测）
    QRect m_rect;
    //药水个数
    int m_health_potion;
    //护盾层数
    int m_shield;
    int hero_shooting_add_speed;
    //上帝模式，为了演示部分功能
    bool god;
};

#endif // HERO_H
