#ifndef DEATHPAGE_H
#define DEATHPAGE_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <startpage.h>
#include <QPushButton>
#define WINDOW_LENGTH 1920
#define WINDOW_WIDTH 1080

class deathpage : public QWidget
{
    Q_OBJECT
public:
    explicit deathpage(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);

private:
    QPushButton play_again;
    QPushButton backstart;
signals:

public slots:  void show_page();

};

#endif // DEATHPAGE_H
