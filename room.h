#ifndef ROOM_H
#define ROOM_H
#include "config.h"
#include "enemy.h"
#include "QVector"
class room
{
public:
    room();
    //房间宽度
    int room_width;
    //房间长度
    int room_hight;
    //房间最大左上角二级绝对坐标
    int max_up_left_corner_x;
    int max_up_left_corner_y;
    //房间中心二级绝对坐标
    int center_x;
    int center_y;
    //房间实际左上角坐标
    int up_left_corner_x;
    int up_left_corner_y;
    //房间编号
    int room_number;
    //房间状态（0未开始，1进行中，2已结束）
    int room_end;
    //房间难度系数
    int room_difficulty;
    //房间特异性编号
    int room_identier;
    //房间怪物数量
    int room_enemy_num;
    //房间怪物信息储存
    QVector<enemy> room_enemy_message;
    //房间基本信息初始化
    void InitiRoom();
    //房间其他信息初始化
    void Create_Enemy(int room_difficulty,bool (&m_map_second)[FIRST_ROOM_SIZE*(MAX_ROOM_SIZE+ROAD_LENGTH)][FIRST_ROOM_SIZE*(MAX_ROOM_SIZE+ROAD_LENGTH)]);
    //房间地形随机化生成
    void Room_Randomly_Generated();
    void Room_Generate_1(bool (&m_map_second)[FIRST_ROOM_SIZE*(MAX_ROOM_SIZE+ROAD_LENGTH)][FIRST_ROOM_SIZE*(MAX_ROOM_SIZE+ROAD_LENGTH)]);

};

#endif // ROOM_H
