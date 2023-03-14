#include "chest.h"
#include "config.h"
chest::chest()
{
    chest_picture[0].load(CHEST0_0_PATH);
    chest_picture[1].load(CHEST0_1_PATH);
    chest_picture[2].load(CHEST0_2_PATH);
    chest_picture[3].load(CHEST0_3_PATH);
    chest_picture[4].load(CHEST0_4_PATH);
    chest_picture[5].load(CHEST0_5_PATH);
    chest_picture[6].load(CHEST0_6_PATH);
    //
    chest_state=0;
    chest_now=0;
}
