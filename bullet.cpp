#include "bullet.h"
#include<QtDebug>
bullet::bullet()
{
    //加载子弹资源
    m_bullet[1].load(BULLET_PATH1);
    m_bullet[2].load(BULLET_PATH2);
    m_bullet[3].load(BULLET_PATH3);
    m_bullet[4].load(BULLET_PATH4);
    m_bullet[5].load(BULLET_PATH5);
}
