#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QMainWindow>
#include <QPushButton>
#include "mainscene.h"//子窗口头文件 游戏页面
#include "introduce.h"//子窗口头文件，介绍页面
#define WINDOW_LENGTH 1920
#define WINDOW_WIDTH 1080
class startpage : public QMainWindow
{
    Q_OBJECT

public:
    startpage(QWidget *parent = 0);
    ~startpage();
    //重新PaintEvent事件 画背景图
    void paintEvent(QPaintEvent *);

public slots:
    void hidepage();
    void showpage();
};

#endif // STARTPAGE_H
