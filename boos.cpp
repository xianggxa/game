#include "boos.h"

boos::boos()
{
    m_boos.load(BOOS_PATH);
    //血量
    hp=150;
    //伤害
    attack=2;
    m_rect.setHeight(m_boos.height());
    m_rect.setWidth(m_boos.width());
    time=0;
    //hzc动态内存分配
    int *a=new int[12];
    for(int i=0;i<12;i++)
        a[i]=i*30;
    for(int k=0;k<12;k++)
        degree[k]=a[k];
    delete [] a;
    /*
    for(int i=0;i<12;i++)
        degree[i]=i*30;
    */
    m_index=0;
}

