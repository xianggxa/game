#ifndef MINIROOM_H
#define MINIROOM_H
#include "QPixmap"
#include "config.h"
#include "room.h"

class miniroom:virtual public room
{
public:
    miniroom();
   // QPixmap mini_room;
    int mini_room_x;
    int mini_room_y;
    int mini_room_identier;
    QPixmap mini_room_special;
};

#endif // MINIROOM_H
