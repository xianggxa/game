#ifndef BOMB_H
#define BOMB_H
#include <QPixmap>
#include <QVector>
#include "config.h"
class bomb
{
public:
    bomb();
    //更新信息（播放图片下标、播放间隔）
    void Bomb_UpdateInfo();
public:
    //放爆炸资源数组
    QVector<QPixmap> m_pixarr[20];
    //爆炸形态
    int m_form;
    //图片最大索引
    int m_max_index[10];
    //爆炸位置
    int m_x;
    int m_y;
    //爆炸切图的时间间隔
    int m_recoder;
    //爆炸时加载的图片下标
    int m_index;
};

#endif // BOMB_H
