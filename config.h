#ifndef CONFIG_H
#define CONFIG_H
//窗口长度
#define WINDOW_LENGTH 1920
//窗口宽度
#define WINDOW_WIDTH 1080
//最小房间数
#define MINIMUM_ROOMS 12
//最大房间数
#define MAXIMUM_ROOMS 20
//最大房间大小（二级缩略图）
#define MAX_ROOM_SIZE 39
//最小房间大小（二级缩略图）
#define MIN_ROOM_SIZE 21
#define ROAD_LENGTH 4
//一级缩略图大小
#define FIRST_ROOM_SIZE 11
//二级缩略图到实际地图的放大倍率
#define MAGNIFICATION 80
//墙壁贴图路径
#define WALL1_PATH ":/source/wall1.png"
#define WALL0_0_PATH ":/source/wall0.0.png"
#define WALL0_1_PATH ":/source/wall0.1.png"
#define WALL0_2_PATH ":/source/wall0.2.png"
#define WALL1_1_PATH ":/source/wall1.1.png"
#define WALL1_2_PATH ":/source/wall1.2.png"
#define WALL1_3_PATH ":/source/wall1.3.png"
#define WALL1_4_PATH ":/source/wall1.4.png"
#define WALL2_1_PATH ":/source/wall2.1.png"
#define WALL2_2_PATH ":/source/wall2.2.png"
#define WALL2_3_PATH ":/source/wall2.3.png"
#define WALL2_4_PATH ":/source/wall2.4.png"
#define WALL3_1_PATH ":/source/wall3.1.png"
#define WALL3_2_PATH ":/source/wall3.2.png"
#define WALL3_3_PATH ":/source/wall3.3.png"
#define WALL3_4_PATH ":/source/wall3.4.png"
#define WALL4_1_PATH ":/source/wall4.1.png"
#define WALL4_2_PATH ":/source/wall4.2.png"
#define WALL4_3_PATH ":/source/wall4.3.png"
#define WALL4_4_PATH ":/source/wall4.4.png"
#define WALL5_1_PATH ":/source/wall5.1.png"
#define WALL5_2_PATH ":/source/wall5.2.png"
#define WALL5_3_PATH ":/source/wall5.3.png"
#define WALL5_4_PATH ":/source/wall5.4.png"
#define WALL6_1_PATH ":/source/wall6.1.png"
#define WALL6_2_PATH ":/source/wall6.2.png"
#define WALL6_3_PATH ":/source/wall6.3.png"
#define WALL6_4_PATH ":/source/wall6.4.png"
#define WALL7_1_PATH ":/source/wall7.1.png"
#define WALL7_2_PATH ":/source/wall7.2.png"
#define WALL7_3_PATH ":/source/wall7.3.png"
#define WALL7_4_PATH ":/source/wall7.4.png"
#define WALL8_1_PATH ":/source/wall8.1.png"
#define WALL8_2_PATH ":/source/wall8.2.png"

//地板贴图路径
#define floor1_PATH ":/source/floor1.png"
#define floor2_PATH ":/source/floor2.png"
//屏幕刷新间隔时间
#define GAME_RATE 10
//-----------武器子弹资源图片--------begin-----//
#define BULLET_PATH1 ":/source/Bullet1.png"
#define BULLET_PATH2 ":/source/Bullet2.png"
#define BULLET_PATH3 ":/source/Bullet3.png"
#define BULLET_PATH4 ":/source/Bullet4.png"
#define BULLET_PATH5 ":/source/Bullet5.png"
#define BULLET_PATH6 ":/source/Bullet6.png"
//-----------武器资源图片--------end-----//
#define HERO_BULLET_SPEED 25  //子弹移动速度
//英雄移动速度
#define MOVE_SPEED 10
#define HERO_MOVING_INTERVAL 5 //英雄移动切图时间间隔
//-----------英雄形态图片--------begin-----//
#define HERO_PATHW1 ":/source/HERO_W1.png"
#define HERO_PATHW2 ":/source/HERO_W2.png"
#define HERO_PATHW3 ":/source/HERO_W3.png"
#define HERO_PATHW4 ":/source/HERO_W4.png"
#define HERO_PATHW5 ":/source/HERO_W5.png"
#define HERO_PATHW6 ":/source/HERO_W6.png"
#define HERO_PATHW7 ":/source/HERO_W7.png"
#define HERO_PATHW8 ":/source/HERO_W8.png"
#define HERO_PATHS1 ":/source/HERO_S1.png"
#define HERO_PATHS2 ":/source/HERO_S2.png"
#define HERO_PATHS3 ":/source/HERO_S3.png"
#define HERO_PATHS4 ":/source/HERO_S4.png"
#define HERO_PATHS5 ":/source/HERO_S5.png"
#define HERO_PATHS6 ":/source/HERO_S6.png"
#define HERO_PATHS7 ":/source/HERO_S7.png"
#define HERO_PATHS8 ":/source/HERO_S8.png"
#define HERO_PATHA1 ":/source/HERO_A1.png"
#define HERO_PATHA2 ":/source/HERO_A2.png"
#define HERO_PATHA3 ":/source/HERO_A3.png"
#define HERO_PATHA4 ":/source/HERO_A4.png"
#define HERO_PATHA5 ":/source/HERO_A5.png"
#define HERO_PATHA6 ":/source/HERO_A6.png"
#define HERO_PATHA7 ":/source/HERO_A7.png"
#define HERO_PATHA8 ":/source/HERO_A8.png"
#define HERO_PATHD1 ":/source/HERO_D1.png"
#define HERO_PATHD2 ":/source/HERO_D2.png"
#define HERO_PATHD3 ":/source/HERO_D3.png"
#define HERO_PATHD4 ":/source/HERO_D4.png"
#define HERO_PATHD5 ":/source/HERO_D5.png"
#define HERO_PATHD6 ":/source/HERO_D6.png"
#define HERO_PATHD7 ":/source/HERO_D7.png"
#define HERO_PATHD8 ":/source/HERO_D8.png"
//-----------英雄形态图片--------end-----//
//-----------爆炸资源图片-------begin------//
#define BOMB_PATH1  ":/source/bomb-1.png"
#define BOMB_PATH2  ":/source/bomb-2.png"
#define BOMB_PATH3  ":/source/bomb-3.png"
#define BOMB_PATH4  ":/source/bomb-4.png"
#define BOMB_PATH5  ":/source/bomb-5.png"
#define BOMB_PATHA1 ":/source/Bomba0.png"
#define BOMB_PATHA2 ":/source/Bomba1.png"
#define BOMB_PATHA3 ":/source/Bomba2.png"
#define BOMB_PATHA4 ":/source/Bomba3.png"
#define BOMB_PATHA5 ":/source/Bomba4.png"
#define BOMB_PATHA6 ":/source/Bomba5.png"
#define BOMB_PATHB1 ":/source/Bombb0.png"
#define BOMB_PATHB2 ":/source/Bombb1.png"
#define BOMB_PATHB3 ":/source/Bombb2.png"
#define BOMB_PATHB4 ":/source/Bombb3.png"
#define BOMB_PATHB5 ":/source/Bombb4.png"
#define BOMB_PATHC1 ":/source/Bombc0.png"
#define BOMB_PATHC2 ":/source/Bombc1.png"
#define BOMB_PATHC3 ":/source/Bombc2.png"
#define BOMB_PATHC4 ":/source/Bombc3.png"
#define BOMB_PATHC5 ":/source/Bombc4.png"
#define BOMB_PATHC6 ":/source/Bombc5.png"
#define BOMB_PATHC7 ":/source/Bombc6.png"
#define BOMB_PATHC8 ":/source/Bombc7.png"
#define BOMB_PATHD1 ":/source/Bombd0.png"
#define BOMB_PATHD2 ":/source/Bombd1.png"
#define BOMB_PATHD3 ":/source/Bombd2.png"
#define BOMB_PATHD4 ":/source/Bombd3.png"
#define BOMB_PATHD5 ":/source/Bombd4.png"
#define BOMB_PATHD6 ":/source/Bombd5.png"
#define BOMB_PATHD7 ":/source/Bombd6.png"
//-----------爆炸资源图片--------end-----//
#define BOMB_MAX  5      //爆炸图片最大索引
#define BOMB_INTERVAL 10   //爆炸切图时间间隔
//小怪贴图
#define ENEMY_PATH ":/source/enemy.png"
//小怪子弹发射间隔
#define ENEMY_STRAIGHT_SHOOTING_INTERVAL 50
//小怪圆射子弹发射间隔
#define ENEMY_CIRCLE_SHOOTING_INTERVAL 15
//小怪移动速度
#define ENEMY_SPEED 3
//小怪子弹速度
#define ENEMY_STRAIGHT_BULLET_SPEED 20
#define ENEMY_CIRCLE_BULLET_SPEED 3
//小怪武器
#define ENEMY_BULLET_PATH ":/source/Bullet1.png"
#define BOOS_PATH ":/source/boos.png"
//小地图背景贴图
#define MINI_ROOM_NOW_PATH ":/source/miniroomnow.png"
#define MINI_ROOM_PATH ":/source/miniroom.png"
#define MINI_ROOM_ROAD_PATH ":/source/miniroad.png"
//迷你地图房间大小
#define MINI_ROOM_SIZE 50
//迷你地图间距
#define MINI_ROOM_INTERVAL 20
#define GAME_RES_PATH  "./HERO_ADVENTURE.rcc" //rcc文件路径
//检测距离（自卫半径）
#define SELF_DEFENSE 1000000
//--------------英雄血量图片------------begin//
#define BLOOD_MAX ":/source/HERO_HP.png"
#define BLOOD_MID ":/source/HERO_HPM.png"
#define BLOOD_EMPTY ":/source/HERO_HPE.png"
//--------------英雄血量图片------------end//
//护盾图片
#define SHIELD ":/source/Shield.png"
#define SHIELD_MAX ":/source/HERO_SHIELD.png"
#define SHIELD_MID ":/source/HERO_SHIELDM.png"
#define MOUSE ":/source/MOUSE.png"
//道具
//箱子
#define CHEST0_0_PATH ":/source/chest0.0.png"
#define CHEST0_1_PATH ":/source/chest0.1.png"
#define CHEST0_2_PATH ":/source/chest0.2.png"
#define CHEST0_3_PATH ":/source/chest0.3.png"
#define CHEST0_4_PATH ":/source/chest0.4.png"
#define CHEST0_5_PATH ":/source/chest0.5.png"
#define CHEST0_6_PATH ":/source/chest0.6.png"
//回血
#define PROPS_HEART1_0_PATH ":/source/heart1.0.png"
#define PROPS_HEART1_1_PATH ":/source/heart1.1.png"
#define PROPS_HEART1_2_PATH ":/source/heart1.2.png"
#define PROPS_HEART1_3_PATH ":/source/heart1.3.png"
#define PROPS_HEART2_0_PATH ":/source/heart2.0.png"
#define PROPS_HEART2_1_PATH ":/source/heart2.1.png"
#define PROPS_HEART2_2_PATH ":/source/heart2.2.png"
#define PROPS_HEART2_3_PATH ":/source/heart2.3.png"
//护盾
#define PROPS_SHIELD1_0_PATH ":/source/shield1.0.png"
#define PROPS_SHIELD1_1_PATH ":/source/shield1.1.png"
#define PROPS_SHIELD1_2_PATH ":/source/shield1.2.png"
#define PROPS_SHIELD1_3_PATH ":/source/shield1.3.png"
#define PROPS_SHIELD2_0_PATH ":/source/shield2.0.png"
#define PROPS_SHIELD2_1_PATH ":/source/shield2.1.png"
#define PROPS_SHIELD2_2_PATH ":/source/shield2.2.png"
#define PROPS_SHIELD2_3_PATH ":/source/shield2.3.png"
//钱币
#define PROPS_COINS1_0_PATH ":/source/coin1.0.png"
#define PROPS_COINS1_1_PATH ":/source/coin1.1.png"
#define PROPS_COINS1_2_PATH ":/source/coin1.2.png"
#define PROPS_COINS1_3_PATH ":/source/coin1.3.png"
#define PROPS_COINS1_4_PATH ":/source/coin1.4.png"
#define PROPS_COINS1_5_PATH ":/source/coin1.5.png"
#define PROPS_COINS2_0_PATH ":/source/coin2.0.png"
#define PROPS_COINS2_1_PATH ":/source/coin2.1.png"
#define PROPS_COINS2_2_PATH ":/source/coin2.2.png"
#define PROPS_COINS2_3_PATH ":/source/coin2.3.png"
#define PROPS_COINS2_4_PATH ":/source/coin2.4.png"
#define PROPS_COINS2_5_PATH ":/source/coin2.5.png"
#define PROPS_COINS3_0_PATH ":/source/coin3.0.png"
#define PROPS_COINS3_1_PATH ":/source/coin3.1.png"
#define PROPS_COINS3_2_PATH ":/source/coin3.2.png"
#define PROPS_COINS3_3_PATH ":/source/coin3.3.png"
#define PROPS_COINS3_4_PATH ":/source/coin3.4.png"
#define PROPS_COINS3_5_PATH ":/source/coin3.5.png"
//传送门动画
#define PORTAL1_PATH ":/source/portal1.png"
#define PORTAL2_PATH ":/source/portal2.png"
#define PORTAL3_PATH ":/source/portal3.png"
#define PORTAL4_PATH ":/source/portal4.png"
#define PORTAL5_PATH ":/source/portal5.png"
#define PORTAL6_PATH ":/source/portal6.png"
#define PORTAL7_PATH ":/source/portal7.png"
#define PORTAL8_PATH ":/source/portal8.png"
#define PORTAL9_PATH ":/source/portal9.png"
#define PORTAL10_PATH ":/source/portal10.png"
#define PORTAL11_PATH ":/source/portal11.png"
#define PORTAL12_PATH ":/source/portal12.png"
#define PORTAL13_PATH ":/source/portal13.png"
#define PORTAL14_PATH ":/source/portal14.png"
#define PORTAL15_PATH ":/source/portal15.png"
#define PORTAL16_PATH ":/source/portal16.png"
#define PORTAL17_PATH ":/source/portal17.png"
#define PORTAL18_PATH ":/source/portal18.png"
#define PORTAL19_PATH ":/source/portal19.png"
#define PORTAL20_PATH ":/source/portal20.png"
#define PORTAL21_PATH ":/source/portal21.png"
#define PORTAL22_PATH ":/source/portal22.png"
#define PORTAL23_PATH ":/source/portal23.png"
#define PORTAL24_PATH ":/source/portal24.png"
#define PORTAL25_PATH ":/source/portal25.png"
#define PORTAL26_PATH ":/source/portal26.png"
#define PORTAL27_PATH ":/source/portal27.png"
#define PORTAL28_PATH ":/source/portal28.png"
#define PORTAL29_PATH ":/source/portal29.png"
#define PORTAL30_PATH ":/source/portal30.png"
#define PORTAL31_PATH ":/source/portal31.png"
#define PORTAL32_PATH ":/source/portal32.png"
#define PORTAL33_PATH ":/source/portal33.png"
#define PORTAL34_PATH ":/source/portal34.png"
#define PORTAL35_PATH ":/source/portal35.png"
#define PORTAL36_PATH ":/source/portal36.png"
#define MUSIC ":/source/Sarah Brightman.wav"
#endif // CONFIG_H
