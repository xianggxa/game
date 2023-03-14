#include "weapon.h"

weapon::weapon()
{
    //m_weapon[1].load()
    for(int i=1;i<=6;i++)
        attack[i]=i;
}

//hzc函数重载
weapon::weapon(int a[])
{
    for(int i=0;i<10;i++)
        attack[i]=a[i];
}

