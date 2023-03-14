#ifndef WEAPON_H
#define WEAPON_H
#include "config.h"
#include <QPixmap>
class weapon
{
public:
    weapon();
    //hzc函数重载
    weapon(int a[]);

public:
int attack[10];
QPixmap m_weapon[10];
};

#endif // WEAPON_H
