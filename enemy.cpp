#include "enemy.h"
#include "config.h"
#include "map.h"
#include "qdebug.h"
enemy::enemy()
{
    m_enemy.load(ENEMY_PATH);
   // qDebug()<<"shir";
    m_rect.setHeight(m_enemy.height());
    m_rect.setWidth(m_enemy.width());
    time=0;
     for(int i=0;i<12;i++)
        degree[i]=i*30;
    m_index=0;
}
