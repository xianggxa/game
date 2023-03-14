#include "props.h"
#include "config.h"
/*props::props()
{
    //血量回复
     hp_add = 0;
    //护盾回复
     shield_add = 0;
    //金币增加
     money_add = 0;
    //武器
     weapon_add = 0;
     //播片初始图片
     picture_now=0;

}*/

void props::Props_Blood_init()
{
    int a_a=ran.randfrom_to(1,2);
    if(a_a==1){
        hp_add = 2;
        props_picture[0].load(PROPS_HEART1_0_PATH);
        props_picture[1].load(PROPS_HEART1_1_PATH);
        props_picture[2].load(PROPS_HEART1_2_PATH);
        props_picture[3].load(PROPS_HEART1_3_PATH);
        picture_num=4;
    }else {
       hp_add = 1;
       props_picture[0].load(PROPS_HEART2_0_PATH);
       props_picture[1].load(PROPS_HEART2_1_PATH);
       props_picture[2].load(PROPS_HEART2_2_PATH);
       props_picture[3].load(PROPS_HEART2_3_PATH);
       picture_num=4;
    }
    auto_pick_up=1;

}

void props::Props_Shield_init()
{
    int a_a=ran.randfrom_to(1,2);
    if(a_a==1){
        shield_add = 2;
        props_picture[0].load(PROPS_SHIELD1_0_PATH);
        props_picture[1].load(PROPS_SHIELD1_1_PATH);
        props_picture[2].load(PROPS_SHIELD1_2_PATH);
        props_picture[3].load(PROPS_SHIELD1_3_PATH);
        picture_num=4;
    }else {
       shield_add = 1;
       props_picture[0].load(PROPS_SHIELD2_0_PATH);
       props_picture[1].load(PROPS_SHIELD2_1_PATH);
       props_picture[2].load(PROPS_SHIELD2_2_PATH);
       props_picture[3].load(PROPS_SHIELD2_3_PATH);
       picture_num=4;
    }
    auto_pick_up=1;
}

void props::Props_Money_init()
{
int a_a=rand()%10;
if(a_a<7){
    money_add=1;
    props_picture[0].load(PROPS_COINS1_0_PATH);
    props_picture[1].load(PROPS_COINS1_1_PATH);
    props_picture[2].load(PROPS_COINS1_2_PATH);
    props_picture[3].load(PROPS_COINS1_3_PATH);
    props_picture[4].load(PROPS_COINS1_4_PATH);
    props_picture[5].load(PROPS_COINS1_5_PATH);
}else if(a_a<9){
    money_add=5;
    props_picture[0].load(PROPS_COINS2_0_PATH);
    props_picture[1].load(PROPS_COINS2_1_PATH);
    props_picture[2].load(PROPS_COINS2_2_PATH);
    props_picture[3].load(PROPS_COINS2_3_PATH);
    props_picture[4].load(PROPS_COINS2_4_PATH);
    props_picture[5].load(PROPS_COINS2_5_PATH);
}else{
    money_add=20;
    props_picture[0].load(PROPS_COINS3_0_PATH);
    props_picture[1].load(PROPS_COINS3_1_PATH);
    props_picture[2].load(PROPS_COINS3_2_PATH);
    props_picture[3].load(PROPS_COINS3_3_PATH);
    props_picture[4].load(PROPS_COINS3_4_PATH);
    props_picture[5].load(PROPS_COINS3_5_PATH);
}
picture_num=6;
auto_pick_up=1;
}

void props::Enemy_died_Props_init()
{
   int a_a=ran.randfrom_to(0,2);
   if(a_a==0){
       Props_Shield_init();

   }else if(a_a==1){
       Props_Blood_init();
   }else{
       Props_Money_init();
   }
}

void props::Chest_Props_init()
{

}
