#ifndef CHEST_H
#define CHEST_H
#include "QPixmap"
#include "QRect"
#include "props.h"
class chest
{
public:
    chest();
private:
    //贴图组
    QPixmap chest_picture[7];
    //画布坐标
    int chest_x;
    int chest_y;
    //碰撞框
    QRect chest_rect;
    //掉落道具
    props chest_props;
    //宝箱状态
    //0未开启 1开启动画 2已开启
    int chest_state;
    //宝箱动画
    int chest_now;
    friend class mainscene;
    friend class map;
};

#endif // CHEST_H
