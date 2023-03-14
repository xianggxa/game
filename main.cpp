#include "mainscene.h"
#include <QApplication>
#include "startpage.h"
#include <QResource>
#include<QSound>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //注册外部的二进制资源文件
    //QResource::registerResource(GAME_RES_PATH);

    QSound::play(MUSIC);
    startpage w;
    w.show();

    return a.exec();
}
