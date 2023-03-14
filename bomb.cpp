#include "bomb.h"

bomb::bomb()
{
    //初始化爆炸图片数目
    if(1)
    {
        QPixmap str;
        str.load(BOMB_PATH1);
        m_pixarr[1].push_back(str);
    }
    if(1){
        QPixmap str;
        str.load(BOMB_PATH2);
        m_pixarr[1].push_back(str);
    }
    if(1){
        QPixmap str;
        str.load(BOMB_PATH3);
        m_pixarr[1].push_back(str);
    }
    if(1){
        QPixmap str;
        str.load(BOMB_PATH4);
        m_pixarr[1].push_back(str);
    }
    if(1){
        QPixmap str;
        str.load(BOMB_PATH5);
        m_pixarr[1].push_back(str);
    }
    m_max_index[1]=4;
    if(2){
        QPixmap str;
        str.load(BOMB_PATHA1);
        m_pixarr[2].push_back(str);
    }
    if(2){
        QPixmap str;
        str.load(BOMB_PATHA2);
        m_pixarr[2].push_back(str);
    }
    if(2){
        QPixmap str;
        str.load(BOMB_PATHA3);
        m_pixarr[2].push_back(str);
    }
    if(2){
        QPixmap str;
        str.load(BOMB_PATHA4);
        m_pixarr[2].push_back(str);
    }
    if(2){
        QPixmap str;
        str.load(BOMB_PATHA5);
        m_pixarr[2].push_back(str);
    }
    if(2){
        QPixmap str;
        str.load(BOMB_PATHA6);
        m_pixarr[2].push_back(str);
    }
    m_max_index[2]=5;
    if(3){
        QPixmap str;
        str.load(BOMB_PATHB1);
        m_pixarr[3].push_back(str);
    }
    if(3){
        QPixmap str;
        str.load(BOMB_PATHB2);
        m_pixarr[3].push_back(str);
    }
    if(3){
        QPixmap str;
        str.load(BOMB_PATHB3);
        m_pixarr[3].push_back(str);
    }
    if(3){
        QPixmap str;
        str.load(BOMB_PATHB4);
        m_pixarr[3].push_back(str);
    }
    if(3){
        QPixmap str;
        str.load(BOMB_PATHB5);
        m_pixarr[3].push_back(str);
    }
    m_max_index[3]=4;
    if(4){
        QPixmap str;
        str.load(BOMB_PATHC1);
        m_pixarr[4].push_back(str);
    }
    if(4){
        QPixmap str;
        str.load(BOMB_PATHC2);
        m_pixarr[4].push_back(str);
    }
    if(4){
        QPixmap str;
        str.load(BOMB_PATHC3);
        m_pixarr[4].push_back(str);
    }
    if(4){
        QPixmap str;
        str.load(BOMB_PATHC4);
        m_pixarr[4].push_back(str);
    }
    if(4){
        QPixmap str;
        str.load(BOMB_PATHC5);
        m_pixarr[4].push_back(str);
    }
    if(4){
        QPixmap str;
        str.load(BOMB_PATHC6);
        m_pixarr[4].push_back(str);
    }
    if(4){
        QPixmap str;
        str.load(BOMB_PATHC7);
        m_pixarr[4].push_back(str);
    }
    if(4){
        QPixmap str;
        str.load(BOMB_PATHC8);
        m_pixarr[4].push_back(str);
    }
    m_max_index[4]=7;
    if(5){
        QPixmap str;
        str.load(BOMB_PATHD1);
        m_pixarr[5].push_back(str);
    }
    if(5){
        QPixmap str;
        str.load(BOMB_PATHD2);
        m_pixarr[5].push_back(str);
    }
    if(5){
        QPixmap str;
        str.load(BOMB_PATHD3);
        m_pixarr[5].push_back(str);
    }
    if(5){
        QPixmap str;
        str.load(BOMB_PATHD4);
        m_pixarr[5].push_back(str);
    }
    if(5){
        QPixmap str;
        str.load(BOMB_PATHD5);
        m_pixarr[5].push_back(str);
    }
    if(5){
        QPixmap str;
        str.load(BOMB_PATHD6);
        m_pixarr[5].push_back(str);
    }
    if(5){
        QPixmap str;
        str.load(BOMB_PATHD7);
        m_pixarr[5].push_back(str);
    }
    m_max_index[5]=6;

    //初始化坐标
    m_x= 0;
    m_y= 0;
    //当前播放图片下标
    m_index = 0;
    //爆炸间隔记录
    m_recoder = 0;
}

//hzc函数模板
template <typename T>
bool Min (T a, T b)
{
    if(a < b)
        return true;
    else
        return false;
}

void bomb::Bomb_UpdateInfo()
{
    m_recoder++;
    /*if(m_recoder<BOMB_INTERVAL)
    {
        //记录爆炸间隔未到，直接return，不需要切图
        return;
    }*/
    //hzc函数模板
    if(Min(m_recoder, BOMB_INTERVAL)){
        //记录爆炸间隔未到，直接return，不需要切图
        return;
    }
    //重置记录
    m_recoder = 0;
    //切换爆炸播放图片
    m_index++;
}
