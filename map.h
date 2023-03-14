#ifndef MAP_H
#define MAP_H
#include"config.h"
#include"room.h"
#include"QVector"
#include "QPixmap"
#include "bullet.h"
#include <QQueue>
#include "enemy.h"
#include "miniroom.h"
#include "props.h"
#include "portal.h"
#include "chest.h"
class map
{
public:

    //一级缩略图构造方向
    int m_map_first_direction[2][4] = {{1,0,-1,0},{0,-1,0,1}};
    //一级缩略图
    int m_map_first[FIRST_ROOM_SIZE][FIRST_ROOM_SIZE];
    //一级编号缩略图
    int m_map_first_identifier[FIRST_ROOM_SIZE][FIRST_ROOM_SIZE];
    //房间数目
    int rooms_num;
    //二级缩略图
    bool m_map_second[FIRST_ROOM_SIZE*(MAX_ROOM_SIZE+ROAD_LENGTH)][FIRST_ROOM_SIZE*(MAX_ROOM_SIZE+ROAD_LENGTH)];
    //二级缩略图（房间地板信息，用于检测进入哪个房间）
    bool m_map_second_floor[FIRST_ROOM_SIZE*(MAX_ROOM_SIZE+ROAD_LENGTH)][FIRST_ROOM_SIZE*(MAX_ROOM_SIZE+ROAD_LENGTH)];
    //二级缩略图（地板贴图）
    bool m_map_second_floor_picture[FIRST_ROOM_SIZE*(MAX_ROOM_SIZE+ROAD_LENGTH)][FIRST_ROOM_SIZE*(MAX_ROOM_SIZE+ROAD_LENGTH)];
    //存储房间信息
    QVector<room> room_message;
    //初始房间左上角坐标
    int m_map_up_left_corner_x;
    int m_map_up_left_corner_y;
    //传送门
    portal portal_now;
    //记录传送门旋转信息
    int portal_time;
    //道具变化信息
    int props_time;
    //初始化图标
    QPixmap m_map_wall;
    QPixmap m_map_floor1;
    QPixmap m_map_floor2;
    QPixmap mini_room;
    QPixmap miniroom_now;
    QPixmap miniroad;
    QPixmap blood_max;
    QPixmap blood_mid;
    QPixmap blood_empty;
    QPixmap m_shield;
    QPixmap m_shield_max;
    QPixmap m_shield_mid;
    //墙壁图标
    QPixmap m_map_wall0[3];
    QPixmap m_map_wall1[4];
    QPixmap m_map_wall2[4];
    QPixmap m_map_wall3[4];
    QPixmap m_map_wall4[4];
    QPixmap m_map_wall5[4];
    QPixmap m_map_wall6[4];
    QPixmap m_map_wall7[4];
    QPixmap m_map_wall8[2];
    //QPixmap mini_room;
   //小地图左上角相对移动倍率
    int miniroom_left_move_x=0;
    int miniroom_left_move_y=0;
    //视窗修正坐标
    int m_map_corrected_x;
    int m_map_corrected_y;
    //记录上一个房间
    int room_last_time=0;
    //当前层难度系数
    int m_map_difficulty;
    //射击记录时间
    int shooting_time;
    //存储当前暂时关闭的墙(左x右y)
    QQueue<QPair<int,int> > clossed_wall;
    bool tab_push;
    //判断当前是否有房间事件正在进行 1表示有房间信息正在进行 0则没有
    bool is_room_start();
    //记录当前是否在暂停状态
    bool is_pause;
    //当前是否正在射击
    bool now_shooting;
    //当前是否正在移动
    bool now_move_d;
    bool now_move_a;
    bool now_move_w;
    bool now_move_s;
    //存储当前怪物信息
    QVector<enemy> enemy_message;
    //存储英雄子弹信息
    QVector<bullet> bullet_message;
    //存储小怪子弹的信息
    QVector<bullet> enemy_bullet_message;
    //存储小地图信息
    QVector<miniroom> miniroom_message;
    QVector<QPair<int,int> > mini_road_message;
    QVector<QPair<int,int> > mini_room_connect;
    //存储当前地图上道具信息
    QVector<props> props_message;
    //储存当前地图上箱子信息
    QVector<chest> chests_message;
public:
    map();


    //初始化地图构建
    void InitiBuild();
    //初始化一级缩略图
    void InitiFirst_map();
    //初始化二级缩略图
    void InitiSecond_map();
    //初始化原始坐标
    void InitiPosition();
    //载入地图所使用图标
    void LoadPicture();
    //判断所处房间信息(返回当前人物所处房间特异性编号，不在房间内则返回0)
    int Room_Judge();
    //关闭当前房间(room_ident 房间特异性编号)
    void Room_Close(int room_ident);
    //打开当前房间
    void Room_Open();

};

#endif // MAP_H
