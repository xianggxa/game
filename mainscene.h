#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include "map.h"
#include "config.h"
#include "QTimer"
#include <QKeyEvent>
#include <QMouseEvent>
#include "bullet.h"
#include "hero.h"
#include "bomb.h"
#include <QVector>
#include "weapon.h"
#include "chest.h"
#include "boos.h"
#include <QPushButton>
#include <QPropertyAnimation>
#include <deathpage.h>
class mainscene : public QWidget
{
    Q_OBJECT

public:
    mainscene(QWidget *parent = 0);
    ~mainscene();
    QTimer m_timer;
    map m_map;
    void InitiScene();
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    //鼠标事件
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    //视窗改变
    void SceneChange();
    //开始游戏
    void Play_Game();
    //创建子弹
    void CreateBullet(double k,int dx,int dy,int flag,int cur,int bullet_form,int speed);
    //初始化英雄坐标
    void InitHeroPosition();
    //英雄移动
    void Hero_Move();
    //更新子弹坐标
    void Bullet_UpdatePosition();
    //碰撞检测
    void collisionDetection();
    //爆炸效果更新
    void Bomb_UpdatePosition();
    //创建爆炸数组元素
    void Create_Bomb(int x,int y,int k);
    void Room_Start_Init(int room_n);
    //更新所有载入信息（非坐标非碰撞框）
    void Updata_AllMessage();
    //将当前房间加入小地图
    void Add_Miniroom(int room_n);
    //射击
    void Shooting();
    //移动
    void Moving();
    //创建BOOS
    void Create_Boos();
    //失败页面
    void Update_Deathmessage();
    //定时
    void Qtimer();
    //爆炸数组
    QVector<bomb>m_bombs;
    //实例化
    hero LEO;
    boos enemy_boos;
    weapon arsenal;

private slots:
     void close_page();
public slots:
     void open_page();
signals:
     void show_deathpage();
     void close_mainscene();
private:
    QTimer *mtimer;
    QTimer *ttime;
};

#endif // MAINSCENE_H
