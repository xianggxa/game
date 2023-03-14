#ifndef PROPS_H
#define PROPS_H

#include "QPixmap"

template<typename T>
class random
{
public:
    T randfrom_to(T from,T to)
    {
        T num=rand()%(to-from+1)+from;
        return num;
    }
};

class props
{
public:

    //血量回复
    int hp_add;
    //护盾回复
    int shield_add;
    //金币增加
    int money_add;
    //武器
    int weapon_add;
    //画布坐标
    int props_x;
    int props_y;
    //是否自动拾取
    bool auto_pick_up;
    //播片信息
    //图片总数
    int picture_num;
    //当前图片
    int picture_now;

    //回血
    void Props_Blood_init();
    //回盾
    void Props_Shield_init();
    //金币
    void Props_Money_init();
    //怪物死亡后的掉落生成
    void Enemy_died_Props_init();
    //宝箱道具生成
    void Chest_Props_init();
    //坐标初始化
    //void Props_xy_init();
    //贴图
    QPixmap props_picture[6];
    //碰撞检测框
    QRect props_rect;
    random<int> ran;
public:
    //props();
    //hzc初始化列表
    props():hp_add(0),shield_add(0),money_add(0),weapon_add(0),picture_now(0){

    }

};


#endif // PROPS_H
