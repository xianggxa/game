#ifndef INTRODUCE_H
#define INTRODUCE_H

#include <QWidget>
#include <QPushButton>
#define WINDOW_LENGTH 1920
#define WINDOW_WIDTH 1080
class introduce : public QWidget
{
    Q_OBJECT
public:
    explicit introduce(QWidget *parent = 0);

    void SendSlot();
    void paintEvent(QPaintEvent *);

private:
    QPushButton back_start2;

private slots:
     void changeSlot();

public slots:
    void show_introduce();

signals:
    void mySignal();

};

#endif // INTRODUCE_H
