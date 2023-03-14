#include "hero.h"
hero::hero()
{
    if(1)
    {
        QPixmap str;
        str.load(HERO_PATHW1);
        m_hero[1].push_back(str);
    }
    if(1)
    {
        QPixmap str;
        str.load(HERO_PATHW2);
        m_hero[1].push_back(str);
    }
    if(1)
    {
        QPixmap str;
        str.load(HERO_PATHW3);
        m_hero[1].push_back(str);
    }
    if(1)
    {
        QPixmap str;
        str.load(HERO_PATHW4);
        m_hero[1].push_back(str);
    }
    if(1)
    {
        QPixmap str;
        str.load(HERO_PATHW5);
        m_hero[1].push_back(str);
    }
    if(1)
    {
        QPixmap str;
        str.load(HERO_PATHW6);
        m_hero[1].push_back(str);
    }
    if(1)
    {
        QPixmap str;
        str.load(HERO_PATHW7);
        m_hero[1].push_back(str);
    }
    if(1)
    {
        QPixmap str;
        str.load(HERO_PATHW8);
        m_hero[1].push_back(str);
    }
    if(2)
    {
        QPixmap str;
        str.load(HERO_PATHS1);
        m_hero[2].push_back(str);
    }
    if(2)
    {
        QPixmap str;
        str.load(HERO_PATHS2);
        m_hero[2].push_back(str);
    }
    if(2)
    {
        QPixmap str;
        str.load(HERO_PATHS3);
        m_hero[2].push_back(str);
    }
    if(2)
    {
        QPixmap str;
        str.load(HERO_PATHS4);
        m_hero[2].push_back(str);
    }
    if(2)
    {
        QPixmap str;
        str.load(HERO_PATHS5);
        m_hero[2].push_back(str);
    }
    if(2)
    {
        QPixmap str;
        str.load(HERO_PATHS6);
        m_hero[2].push_back(str);
    }
    if(2)
    {
        QPixmap str;
        str.load(HERO_PATHS7);
        m_hero[2].push_back(str);
    }
    if(2)
    {
        QPixmap str;
        str.load(HERO_PATHS8);
        m_hero[2].push_back(str);
    }
    if(3)
    {
        QPixmap str;
        str.load(HERO_PATHA1);
        m_hero[3].push_back(str);
    }
    if(3)
    {
        QPixmap str;
        str.load(HERO_PATHA2);
        m_hero[3].push_back(str);
    }
    if(3)
    {
        QPixmap str;
        str.load(HERO_PATHA3);
        m_hero[3].push_back(str);
    }
    if(3)
    {
        QPixmap str;
        str.load(HERO_PATHA4);
        m_hero[3].push_back(str);
    }
    if(3)
    {
        QPixmap str;
        str.load(HERO_PATHA5);
        m_hero[3].push_back(str);
    }
    if(3)
    {
        QPixmap str;
        str.load(HERO_PATHA6);
        m_hero[3].push_back(str);
    }
    if(3)
    {
        QPixmap str;
        str.load(HERO_PATHA7);
        m_hero[3].push_back(str);
    }
    if(3)
    {
        QPixmap str;
        str.load(HERO_PATHA8);
        m_hero[3].push_back(str);
    }
    if(4)
    {
        QPixmap str;
        str.load(HERO_PATHD1);
        m_hero[4].push_back(str);
    }
    if(4)
    {
        QPixmap str;
        str.load(HERO_PATHD2);
        m_hero[4].push_back(str);
    }
    if(4)
    {
        QPixmap str;
        str.load(HERO_PATHD3);
        m_hero[4].push_back(str);
    }
    if(4)
    {
        QPixmap str;
        str.load(HERO_PATHD4);
        m_hero[4].push_back(str);
    }
    if(4)
    {
        QPixmap str;
        str.load(HERO_PATHD5);
        m_hero[4].push_back(str);
    }
    if(4)
    {
        QPixmap str;
        str.load(HERO_PATHD6);
        m_hero[4].push_back(str);
    }
    if(4)
    {
        QPixmap str;
        str.load(HERO_PATHD7);
        m_hero[4].push_back(str);
    }
    if(4)
    {
        QPixmap str;
        str.load(HERO_PATHD8);
        m_hero[4].push_back(str);
    }
    m_level=1;
    m_hp=16;
    m_hp_limit=8;
    m_experience=0;
    m_health_potion=0;
    m_shield=2;
    m_index=0;
    m_recoder=0;
    m_direction=1;
    now_weapon_num=2;
    m_weapon_index=1;
    m_weapon[1]=1;
    m_weapon[2]=2;
}
void hero::Hero_UpdateInfo()
{
    m_recoder++;
    if(m_recoder<=HERO_MOVING_INTERVAL)
    {
        //记录切图间隔未到，直接return，不需要切图
        return;
    }
    //重置记录
    m_recoder = 0;
    //切换行走播放图片
    m_index=m_index<=6?(m_index+1):0;
}
