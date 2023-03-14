#include "room.h"
#include "QtGlobal"
#include "QTime"
room::room()
{

}

void room::InitiRoom()
{
    //qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    //房间设定未开始状态
    room_end=0;
    //随机化计算房间大小
    room_hight=qrand()%(MAX_ROOM_SIZE-MIN_ROOM_SIZE+1)+MIN_ROOM_SIZE;
    room_width=qrand()%(MAX_ROOM_SIZE-MIN_ROOM_SIZE+1)+MIN_ROOM_SIZE;
    //room_hight=MAX_ROOM_SIZE;
     //room_width=MAX_ROOM_SIZE;
    //计算中心绝对坐标
    center_x=max_up_left_corner_x+MAX_ROOM_SIZE/2;
    center_y=max_up_left_corner_y+MAX_ROOM_SIZE/2;
    //计算实际房间左上角绝对坐标
    up_left_corner_x=center_x-room_width/2;
    up_left_corner_y=center_y-room_hight/2;

}

void room::Create_Enemy(int room_difficulty,bool (&m_map_second)[FIRST_ROOM_SIZE*(MAX_ROOM_SIZE+ROAD_LENGTH)][FIRST_ROOM_SIZE*(MAX_ROOM_SIZE+ROAD_LENGTH)])
{

    int temp=qrand()%3+1;
    //敌人数量

    int num=temp;
    room_enemy_num=num;
    //生成敌人
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i_i=0;i_i<num;i_i++){

        enemy a_a;
        temp=qrand()%2+1;
        a_a.enemy_type=temp;
        a_a.attack=5;
        a_a.hp=10;
        a_a.time=0;
        while(1){
            int x=qrand()%(room_width*MAGNIFICATION),y=qrand()%(room_hight*MAGNIFICATION);
            int w=a_a.m_enemy.width(),h=a_a.m_enemy.height();
            int tcx=up_left_corner_x*MAGNIFICATION,tcy=up_left_corner_y*MAGNIFICATION;
            int tcx1=(tcx+x)/MAGNIFICATION,tcy1=(tcy+y)/MAGNIFICATION;
            int tcx2=(tcx+w+x)/MAGNIFICATION,tcy2=tcy1;
            int tcx3=tcx1,tcy3=(tcy+h+y)/MAGNIFICATION;
            int tcx4=tcx2,tcy4=tcy3;
            if(!m_map_second[tcy1][tcx1]&&!m_map_second[tcy2][tcx2]&&!m_map_second[tcy3][tcx3]&&!m_map_second[tcy4][tcx4])
            {
                a_a.enemy_left_coner_x=tcx+x;
                a_a.enemy_left_coner_y=tcy+y;
                break;
            }
        }
        a_a.m_x=a_a.enemy_left_coner_x;
        a_a.m_y=a_a.enemy_left_coner_y;
        room_enemy_message.append(a_a);
    }
}


void room::Room_Randomly_Generated()
{

}

void room::Room_Generate_1(bool (&m_map_second)[FIRST_ROOM_SIZE*(MAX_ROOM_SIZE+ROAD_LENGTH)][FIRST_ROOM_SIZE*(MAX_ROOM_SIZE+ROAD_LENGTH)])
{
    //qsrand(time(0));
    //int a=qrand()%2;
    /*if(!a)
    {
            int a_a=rand()%2;
            a_a=0;
            int z;
            if(a_a==0)
                z=1;
            else if(a_a==1)
                z=0;
             if(room_hight<room_width){

                 for(int i=1,dis=room_width/4;i<=3;i++,z^=1){

                     int len=rand()%4+room_hight-11;
                     int k=(z==0?1:-1);
                     //修正值
                     int l=(i==2?3:0);
                     for(int j=0;j<=len-l;j++){
                        m_map_second[up_left_corner_y+(room_hight-1)*z+j*k+l*k][up_left_corner_x+i*dis]=1;
                     }

                 }

             }else {
                 for(int i=1,dis=room_hight/4;i<=3;i++,z^=1){

                     int len=rand()%4+room_width-11;
                     int k=(z==0?1:-1);
                     //修正值
                     int l=(i==2?3:0);
                     for(int j=0;j<=len-l;j++)
                        m_map_second[up_left_corner_y+i*dis][up_left_corner_x+(room_width-1)*z+j*k+l*k]=1;

                     }

             }
    }//else */

        /*if(room_hight<room_width){
            int x=center_x+3;
            int y=up_left_corner_y;
            int x1=center_x-4;
            int y1=up_left_corner_y+room_hight-1;
            for(int i=0,k=1,l=-1;i<room_width/2-2;i++){
                m_map_second[y+k*i][x+l*i]=1;
                m_map_second[y+k*i+1][x+l*i]=1;

                m_map_second[y1+l*i][x1+k*i]=1;
                m_map_second[y1+l*i-1][x1+k*i]=1;
            }
        }else {
            int y=center_y-4;
            int x=up_left_corner_x;
            int y1=center_y+4;
            int x1=up_left_corner_x+room_width-1;
            for(int i=0,k=1,l=-1;i<room_hight/2-2;i++){
                m_map_second[y+k*i][x+k*i]=1;
                m_map_second[y+k*i-1][x+k*i]=1;
               // m_map_second[y+k*i+1][x+k*i]=1;
                m_map_second[y1+l*i][x1+l*i]=1;
               // m_map_second[y1+l*i-1][x1+l*i]=1;
                m_map_second[y1+l*i+1][x1+l*i]=1;
            }
        }
    //1
    //1 0 1
    //0 1 0
    //1 0 1
        /*int x1=up_left_corner_x+2;
        int y1=up_left_corner_y+2;
        int x2=up_left_corner_x+room_width-3;
        int y2=up_left_corner_y+room_hight-3;
        int k=1,l=-1;
        for(int i=0;i<(room_width<room_hight?room_width/2:room_hight/2)-4;i++){
            m_map_second[y1+k*i][x1+k*i]=1;
            m_map_second[y1+k*i][x2+l*i]=1;
            m_map_second[y2+l*i][x2+l*i]=1;
            m_map_second[y2+l*i][x1+k*i]=1;
        }*/
//2
    //0 1 0
    //1 0 1
    //0 1 0
/*
        int x1=up_left_corner_x+3;
        int y1=up_left_corner_y+3;

        int x2=center_x;
        int y2=center_y;
        int x3=up_left_corner_x+room_width-4;
        int y3=up_left_corner_y+room_hight-4;
        int k=1,l=-1;
        for(int i=0;i<(room_width<room_hight?room_width/2:room_hight/2)-6;i++){
            m_map_second[y1+k*i][x2]=1;
            m_map_second[y2][x1+k*i]=1;
            m_map_second[y3+l*i][x2]=1;
            m_map_second[y2][x3+l*i]=1;
        }*/
        //3
    //1 1 0 1 1
    //1 0 0 0 1
    //0 0 0 0 0
    //1 0 0 0 1
    //1 1 0 1 1
       /* int x1=up_left_corner_x+4;
        int y1=up_left_corner_y+4;
        int x2=up_left_corner_x+room_width-5;
        int y2=up_left_corner_y+room_hight-5;
        int k=1,l=-1;
        int len=(std::max(room_width,room_hight))/2-5;
        //分支 i=0 或i=1;
        for(int i=1;i<(7<len?7:len);i++){
            m_map_second[y1+k*i][x1]=1;
            m_map_second[y1][x1+k*i]=1;
            m_map_second[y2+l*i][x1]=1;
            m_map_second[y2][x1+k*i]=1;
            m_map_second[y2+l*i][x2]=1;
            m_map_second[y2][x2+l*i]=1;
            m_map_second[y1+k*i][x2]=1;
            m_map_second[y1][x2+l*i]=1;
        }*/
        //4 实心矩形 23以下直接跳过
        /*int x1=up_left_corner_x+4;
        int y1=up_left_corner_y+4;
        int x2=up_left_corner_x+room_width-5;
        int y2=up_left_corner_y+room_hight-5;
        int k=1,l=-1;
        int aa=rand()%3+3;

        for(int i=0;i<aa;i++){
            for(int j=0;j<aa;j++){
                m_map_second[y1+j*k][x1+i*k]=1;
                m_map_second[y2+l*j][x1+i*k]=1;
                m_map_second[y1+j*k][x2+l*i]=1;
                m_map_second[y2+l*j][x2+l*i]=1;
            }
        }*/
//5
    if(room_width>room_hight){
        int h1=(room_hight-2)/4;
        int s1=(room_width-2)/5;
        //left up corner
        m_map_second[up_left_corner_y+h1+1][up_left_corner_x+s1+1]=1;
        m_map_second[up_left_corner_y+h1-1+1][up_left_corner_x+s1+1]=1;
        m_map_second[up_left_corner_y+h1-2+1][up_left_corner_x+s1+1]=1;
        m_map_second[up_left_corner_y+h1-2+1][up_left_corner_x+s1+1+1]=1;
        m_map_second[up_left_corner_y+h1-2+1][up_left_corner_x+s1+2+1]=1;
        m_map_second[up_left_corner_y+h1+1][up_left_corner_x+s1-1+1]=1;
        m_map_second[up_left_corner_y+h1+1][up_left_corner_x+s1-2+1]=1;
        //left down corner
        m_map_second[up_left_corner_y+room_hight-1-h1-1][up_left_corner_x+s1+1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1+1-1][up_left_corner_x+s1+1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1+2-1][up_left_corner_x+s1+1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1+2-1][up_left_corner_x+s1+1+1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1+2-1][up_left_corner_x+s1+2+1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1-1][up_left_corner_x+s1-1+1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1-1][up_left_corner_x+s1-2+1]=1;
        //right up corner
        m_map_second[up_left_corner_y+h1+1][up_left_corner_x+room_width-1-s1-1]=1;
        m_map_second[up_left_corner_y+h1-1+1][up_left_corner_x+room_width-1-s1-1]=1;
        m_map_second[up_left_corner_y+h1-2+1][up_left_corner_x+room_width-1-s1-1]=1;
        m_map_second[up_left_corner_y+h1-2+1][up_left_corner_x+room_width-1-s1-1-1]=1;
        m_map_second[up_left_corner_y+h1-2+1][up_left_corner_x+room_width-1-s1-2-1]=1;
        m_map_second[up_left_corner_y+h1+1][up_left_corner_x+room_width-1-s1+1-1]=1;
        m_map_second[up_left_corner_y+h1+1][up_left_corner_x+room_width-1-s1+2-1]=1;
        //right down corner
        m_map_second[up_left_corner_y+room_hight-1-h1-1][up_left_corner_x+room_width-1-s1-1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1+1-1][up_left_corner_x+room_width-1-s1-1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1+2-1][up_left_corner_x+room_width-1-s1-1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1-1][up_left_corner_x+room_width-1-s1+1-1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1-1][up_left_corner_x+room_width-1-s1+2-1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1+2-1][up_left_corner_x+room_width-1-s1-1-1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1+2-1][up_left_corner_x+room_width-1-s1-2-1]=1;
    }else {
        int h1=(room_hight-2)/5;
        int s1=(room_width-2)/4;
        //left up corner
        m_map_second[up_left_corner_y+h1+1][up_left_corner_x+s1+1]=1;
        m_map_second[up_left_corner_y+h1-1+1][up_left_corner_x+s1+1]=1;
        m_map_second[up_left_corner_y+h1-2+1][up_left_corner_x+s1+1]=1;
        m_map_second[up_left_corner_y+h1+1][up_left_corner_x+s1-1+1]=1;
        m_map_second[up_left_corner_y+h1+1][up_left_corner_x+s1-2+1]=1;
        m_map_second[up_left_corner_y+h1+1+1][up_left_corner_x+s1-2+1]=1;
        m_map_second[up_left_corner_y+h1+2+1][up_left_corner_x+s1-2+1]=1;
        //left down corner
        m_map_second[up_left_corner_y+room_hight-1-h1-1][up_left_corner_x+s1+1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1+1-1][up_left_corner_x+s1+1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1+2-1][up_left_corner_x+s1+1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1-1][up_left_corner_x+s1-1+1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1-1][up_left_corner_x+s1-2+1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1-1-1][up_left_corner_x+s1-2+1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1-2-1][up_left_corner_x+s1-2+1]=1;
        //right up corner
        m_map_second[up_left_corner_y+h1+1][up_left_corner_x+room_width-1-s1-1]=1;
        m_map_second[up_left_corner_y+h1-1+1][up_left_corner_x+room_width-1-s1-1]=1;
        m_map_second[up_left_corner_y+h1-2+1][up_left_corner_x+room_width-1-s1-1]=1;
        m_map_second[up_left_corner_y+h1+1][up_left_corner_x+room_width-1-s1+1-1]=1;
        m_map_second[up_left_corner_y+h1+1][up_left_corner_x+room_width-1-s1+2-1]=1;
        m_map_second[up_left_corner_y+h1+1+1][up_left_corner_x+room_width-1-s1+2-1]=1;
        m_map_second[up_left_corner_y+h1+2+1][up_left_corner_x+room_width-1-s1+2-1]=1;
        //right down corner
        m_map_second[up_left_corner_y+room_hight-1-h1-1][up_left_corner_x+room_width-1-s1-1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1+1-1][up_left_corner_x+room_width-1-s1-1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1+2-1][up_left_corner_x+room_width-1-s1-1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1-1][up_left_corner_x+room_width-1-s1+1-1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1-1][up_left_corner_x+room_width-1-s1+2-1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1-1-1][up_left_corner_x+room_width-1-s1+2-1]=1;
        m_map_second[up_left_corner_y+room_hight-1-h1-2-1][up_left_corner_x+room_width-1-s1+2-1]=1;
    }

        //center
        //1十字
        /*m_map_second[center_x][center_y]=1;
        for(int i=1;i<3;i++){
             m_map_second[center_x+i][center_y]=1;
             m_map_second[center_x-i][center_y]=1;
             m_map_second[center_x][center_y+i]=1;
             m_map_second[center_x][center_y-i]=1;
        }*/
        /*//2实心 3*3
        int x=center_x-1;
        int y=center_y-1;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++)
                m_map_second[y+j][x+i]=1;
        }*/
        //3叉
        /*for(int i=0;i<3;i++){
            m_map_second[center_x+i][center_y+i]=1;
            m_map_second[center_x-i][center_y+i]=1;
            m_map_second[center_x-i][center_y-i]=1;
            m_map_second[center_x+i][center_y-i]=1;
        }*/
        //








}
