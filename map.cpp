#include "map.h"
#include "QQueue"
#include "QtGlobal"
#include "QDebug"
#include <time.h>
map::map()
{
    InitiBuild();
    //初始时无上一次所在房间
  room_last_time=0;
  tab_push=0;
  now_shooting=0;
  now_move_d=0;
  now_move_a=0;
   now_move_w=0;
  now_move_s=0;
  shooting_time=0;
  m_map_corrected_x=0;
  m_map_corrected_y=0;
  is_pause=0;
  portal_time=0;
  props_time=0;
}

void map::InitiBuild()
{
    InitiFirst_map();
    InitiSecond_map();
    InitiPosition();
    LoadPicture();
}

void map::InitiFirst_map()
{
    srand(time(0));
    m_map_first[FIRST_ROOM_SIZE/2][FIRST_ROOM_SIZE/2]=1;
    //初始化房间数
    rooms_num=rand()%(MAXIMUM_ROOMS-MINIMUM_ROOMS+1)+MINIMUM_ROOMS;
    int rooms_num_use=rooms_num;
    //用于bfs随机生成使用的元素
    struct bfs_element{

        int x_;
        int y_;
        //房间编号，差为1的相邻两房间相通
        int room_number_;
    };
    QQueue<bfs_element> bfs_queue;

    bfs_queue.enqueue({FIRST_ROOM_SIZE/2,FIRST_ROOM_SIZE/2,1});

    while(!bfs_queue.isEmpty()){
        //取出头部元素进行随机扩展
        int x=bfs_queue.head().x_;
        int y=bfs_queue.head().y_;
        int room_number_now=bfs_queue.head().room_number_+1;

        bfs_queue.dequeue();
        if(!rooms_num_use)
            return ;
        //可以走的方向数
        int direction_num=0;
        //随机后决定走的方向数
        int re_direction_num=0;
        //修正值
        int correction_value=0;

        for(int i=0; i<4; i++)
        {
            if((x+m_map_first_direction[0][i])==-1||(y+m_map_first_direction[1][i])==-1||(y+m_map_first_direction[1][i])==12||(x+m_map_first_direction[0][i])==12)
                continue;
            if(!m_map_first[x+m_map_first_direction[0][i]][y+m_map_first_direction[1][i]])
                direction_num++;
        }
        //保证修正值
        if(direction_num==4||bfs_queue.isEmpty())
            correction_value=1;
        //随机化每个节点延伸出实际走的道路数
        re_direction_num=qrand()%(direction_num+1);

        if(!re_direction_num)re_direction_num+=correction_value;

        while(1){

            if(!re_direction_num)
                break;

            int i=qrand()%4;
            int x1=x+m_map_first_direction[0][i];
            int y1=y+m_map_first_direction[1][i];
            //如果越界或者本身已经经过
            if(x1==-1||y1==-1||(m_map_first[x1][y1])||x1==12||y1==12)
                continue;

            re_direction_num--;
            rooms_num_use--;
            if(!rooms_num_use){

                m_map_first[x1][y1]=30;
                return ;
            }m_map_first[x1][y1]=room_number_now;

            bfs_queue.enqueue({x1,y1,room_number_now});


        }

    }


}

void map::InitiSecond_map()
{
    //对一级缩略图上定为房间的点进行房间初始化处理
    int identier = 1;
    for(int i=0;i<FIRST_ROOM_SIZE;i++){
        for(int j=0;j<FIRST_ROOM_SIZE;j++){
            if(m_map_first[i][j]){
                room a_a;
                //特异化编号标记
                a_a.room_identier=identier++;
                //编号标记返回映射到一级缩略图
                m_map_first_identifier[i][j]=a_a.room_identier;
                a_a.max_up_left_corner_x=j*(MAX_ROOM_SIZE+ROAD_LENGTH);
                a_a.max_up_left_corner_y=i*(MAX_ROOM_SIZE+ROAD_LENGTH);
                a_a.InitiRoom();
                //boss房的特殊处理
                if(m_map_first[i][j]==30){
                    a_a.room_hight=MAX_ROOM_SIZE;
                    a_a.room_width=MAX_ROOM_SIZE;
                    a_a.up_left_corner_x=a_a.center_x-a_a.room_width/2;
                    a_a.up_left_corner_y=a_a.center_y-a_a.room_hight/2;
                }//对于初始房间，其本身属于已经结束的房间
                else if((i==FIRST_ROOM_SIZE/2)&&j==(FIRST_ROOM_SIZE/2))
                        a_a.room_end=2;




                //覆盖房间地图信息到二级缩略图
                for(int i_i=0;i_i<a_a.room_width;i_i++){
                    m_map_second[a_a.up_left_corner_y][a_a.up_left_corner_x+i_i]=1;
                    m_map_second[a_a.up_left_corner_y+a_a.room_hight-1][a_a.up_left_corner_x+i_i]=1;
                }

                for(int i_i=0;i_i<a_a.room_hight;i_i++){
                    m_map_second[a_a.up_left_corner_y+i_i][a_a.up_left_corner_x]=1;
                    m_map_second[a_a.up_left_corner_y+i_i][a_a.up_left_corner_x+a_a.room_width-1]=1;
                }
                for(int i_i=1;i_i<a_a.room_width-1;i_i++){
                    for(int j_j=1;j_j<a_a.room_hight-1;j_j++){
                        m_map_second_floor[j_j+a_a.up_left_corner_y][i_i+a_a.up_left_corner_x]=1;
                        //二级缩略图贴图随机化
                         m_map_second_floor_picture[j_j+a_a.up_left_corner_y][i_i+a_a.up_left_corner_x]=bool(rand()%2);
                    }
                }
                //将创建出来的房间信息储存
                room_message.append(a_a);

            }
        }
    }
    for(int i=0;i<FIRST_ROOM_SIZE;i++){
        for(int j=0;j<FIRST_ROOM_SIZE;j++){
            if(m_map_first[i][j]){
                //QDebug()<<m_map_first[i][j];
                int l_l=m_map_first[i][j];
                int x1;
                int y1;
                //枚举四个方向是否存在道路
                for(int k=0;k<4;k++){
                    x1=j+m_map_first_direction[0][k];
                    y1=i+m_map_first_direction[1][k];
                    //如果相邻两者连通
                    if((l_l==(m_map_first[y1][x1]+1)&&m_map_first[y1][x1])||(l_l==30&&m_map_first[y1][x1])){
                        int x_c1=j*(MAX_ROOM_SIZE+ROAD_LENGTH)+MAX_ROOM_SIZE/2;
                        int y_c1=i*(MAX_ROOM_SIZE+ROAD_LENGTH)+MAX_ROOM_SIZE/2;
                        int x_c2=x1*(MAX_ROOM_SIZE+ROAD_LENGTH)+MAX_ROOM_SIZE/2;
                        int y_c2=y1*(MAX_ROOM_SIZE+ROAD_LENGTH)+MAX_ROOM_SIZE/2;
                        if(x_c1==x_c2){
                            if(y_c2<y_c1)
                                std::swap(y_c2,y_c1);
                            for(int i_i=y_c1,tag=0;i_i!=y_c2;i_i++){
                                if(m_map_second[i_i][x_c1]){
                                    tag^=1;
                                    m_map_second[i_i][x_c1]=0;
                                    m_map_second[i_i][x_c1-1]=0;
                                    m_map_second[i_i][x_c1+1]=0;
                                }

                                if(tag){
                                    m_map_second[i_i][x_c1+2]=1;
                                    m_map_second[i_i][x_c1-2]=1;
                                }

                            }
                        }else {
                            if(x_c2<x_c1)
                                std::swap(x_c1,x_c2);
                            for(int i_i=x_c1,tag=0;i_i!=x_c2;i_i++){
                                if(m_map_second[y_c1][i_i]){
                                    tag^=1;
                                    m_map_second[y_c1][i_i]=0;
                                    m_map_second[y_c1+1][i_i]=0;
                                    m_map_second[y_c1-1][i_i]=0;
                                }
                                if(tag){
                                    m_map_second[y_c1+2][i_i]=1;
                                    m_map_second[y_c1-2][i_i]=1;
                                }
                            }

                        }
                    }
                }

            }
        }
    }
    for(int i_i=0;i_i<room_message.size();i_i++){
        //普通房间的地形初始化
        if(room_message[i_i].room_end!=2)
        room_message[i_i].Room_Generate_1(m_map_second);
    }
    //
    for(int i_i=0;i_i<room_message.size();i_i++){
        room_message[i_i].Create_Enemy(1,m_map_second);
    }

}

void map::InitiPosition()
{
    m_map_up_left_corner_x=(FIRST_ROOM_SIZE/2*(MAX_ROOM_SIZE+ROAD_LENGTH)+MAX_ROOM_SIZE/2)*MAGNIFICATION-WINDOW_LENGTH/2;
    m_map_up_left_corner_y=(FIRST_ROOM_SIZE/2*(MAX_ROOM_SIZE+ROAD_LENGTH)+MAX_ROOM_SIZE/2)*MAGNIFICATION-WINDOW_WIDTH/2;

}

void map::LoadPicture()
{
    blood_max.load(BLOOD_MAX);
    blood_mid.load(BLOOD_MID);
    blood_empty.load(BLOOD_EMPTY);
    m_shield.load(SHIELD);
    m_shield_max.load(SHIELD_MAX);
    m_shield_mid.load(SHIELD_MID);
    //载入图标
    m_map_wall.load(WALL1_PATH);
    m_map_floor1.load(floor1_PATH);
    m_map_floor2.load(floor2_PATH);
    miniroom_now.load(MINI_ROOM_NOW_PATH);
    mini_room.load(MINI_ROOM_PATH);
    miniroad.load(MINI_ROOM_ROAD_PATH);
    m_map_wall0[0].load(WALL0_0_PATH);
    m_map_wall0[1].load(WALL0_1_PATH);
    m_map_wall0[2].load(WALL0_2_PATH);
    m_map_wall1[0].load(WALL1_1_PATH);
    m_map_wall1[1].load(WALL1_2_PATH);
    m_map_wall1[2].load(WALL1_3_PATH);
    m_map_wall1[3].load(WALL1_4_PATH);
    m_map_wall2[0].load(WALL2_1_PATH);
    m_map_wall2[1].load(WALL2_2_PATH);
    m_map_wall2[2].load(WALL2_3_PATH);
    m_map_wall2[3].load(WALL2_4_PATH);
    m_map_wall3[0].load(WALL3_1_PATH);
    m_map_wall3[1].load(WALL3_2_PATH);
    m_map_wall3[2].load(WALL3_3_PATH);
    m_map_wall3[3].load(WALL3_4_PATH);
    m_map_wall4[0].load(WALL4_1_PATH);
    m_map_wall4[1].load(WALL4_2_PATH);
    m_map_wall4[2].load(WALL4_3_PATH);
    m_map_wall4[3].load(WALL4_4_PATH);
    m_map_wall5[0].load(WALL5_1_PATH);
    m_map_wall5[1].load(WALL5_2_PATH);
    m_map_wall5[2].load(WALL5_3_PATH);
    m_map_wall5[3].load(WALL5_4_PATH);
    m_map_wall6[0].load(WALL6_1_PATH);
    m_map_wall6[1].load(WALL6_2_PATH);
    m_map_wall6[2].load(WALL6_3_PATH);
    m_map_wall6[3].load(WALL6_4_PATH);
    m_map_wall7[0].load(WALL7_1_PATH);
    m_map_wall7[1].load(WALL7_2_PATH);
    m_map_wall7[2].load(WALL7_3_PATH);
    m_map_wall7[3].load(WALL7_4_PATH);
    m_map_wall8[0].load(WALL8_1_PATH);
    m_map_wall8[1].load(WALL8_2_PATH);

}
int map::Room_Judge()
{

    //获取人物此时位置
    int x_x=(m_map_up_left_corner_x+WINDOW_LENGTH/2)/MAGNIFICATION;
    int y_y=(m_map_up_left_corner_y+WINDOW_WIDTH/2)/MAGNIFICATION;

    if(m_map_second_floor[y_y+1][x_x+1]&&m_map_second_floor[y_y-1][x_x-1]&&m_map_second_floor[y_y-1][x_x+1]&&m_map_second_floor[y_y+1][x_x-1])
        return m_map_first_identifier[y_y/(MAX_ROOM_SIZE+ROAD_LENGTH)][x_x/(MAX_ROOM_SIZE+ROAD_LENGTH)];
        //return std::min(std::min(std::min(m_map_first_identifier[y_y/(MAX_ROOM_SIZE+ROAD_LENGTH)+60][x_x/(MAX_ROOM_SIZE+ROAD_LENGTH)+50],m_map_first_identifier[y_y/(MAX_ROOM_SIZE+ROAD_LENGTH)-60][x_x/(MAX_ROOM_SIZE+ROAD_LENGTH)+50]),m_map_first_identifier[y_y/(MAX_ROOM_SIZE+ROAD_LENGTH)-60][x_x/(MAX_ROOM_SIZE+ROAD_LENGTH)-50]),m_map_first_identifier[y_y/(MAX_ROOM_SIZE+ROAD_LENGTH)+60][x_x/(MAX_ROOM_SIZE+ROAD_LENGTH)-50]);
    else return 0;


}

void map::Room_Close(int room_ident)
{
    //取得所处位置坐标
    room a_a=room_message[room_ident-1];
    int x_x=a_a.up_left_corner_x;
    int y_y=a_a.up_left_corner_y;

    for(int i_i=0;i_i<a_a.room_width;i_i++){
        if(!m_map_second[y_y][x_x+i_i]){
            m_map_second[y_y][x_x+i_i]=1;
            clossed_wall.enqueue({(x_x+i_i),y_y});
        }
        if(!m_map_second[y_y+a_a.room_hight-1][x_x+i_i]){
            m_map_second[y_y+a_a.room_hight-1][x_x+i_i]=1;
            clossed_wall.enqueue({(x_x+i_i),(y_y+a_a.room_hight-1)});
        }


    }

    for(int i_i=0;i_i<a_a.room_hight;i_i++){
        if(!m_map_second[y_y+i_i][x_x]&&!m_map_second_floor[y_y+i_i][x_x]){
            m_map_second[y_y+i_i][x_x]=1;
            clossed_wall.enqueue({(x_x),(y_y+i_i)});
        }
        if(!m_map_second[y_y+i_i][x_x+a_a.room_width-1]&&!m_map_second_floor[y_y+i_i][x_x+a_a.room_width-1]){
            m_map_second[y_y+i_i][x_x+a_a.room_width-1]=1;
            clossed_wall.enqueue({(x_x+a_a.room_width-1),(y_y+i_i)});
        }


    }

}

void map::Room_Open()
{

    int x_x,y_y;
    while(!clossed_wall.isEmpty()){

        x_x=clossed_wall.head().first;
        y_y=clossed_wall.head().second;

        clossed_wall.dequeue();
        m_map_second[y_y][x_x]=0;
    }


}
