#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <tower.h>
#include <QList>
#include <QDebug>
#include <QDrag>
#include <my_pushbutton.h>
#include <enermy.h>
//设置最大关卡
const int maxlevel=2;

namespace Ui {
class gamewindow;
}

class gamewindow : public QMainWindow
{
    Q_OBJECT
public:
    int levelindex;
    int waves=0;
    gamewindow(int level);
    ~gamewindow();
    void paintEvent(QPaintEvent *event);
    void loadtowerposition();
//    void loadwaypoint();
    void mousePressEvent(QMouseEvent *event);

    bool canplacetower(QPoint);
    void buildtower(QString ,QPoint);

    bool loadWave();
    void updateMap();
private:
    Ui::gamewindow *ui;
    QList<towerposition> towerposlist;
    QList<tower *> Towerlist;
    QList<Enermy *> Enemylist;
//    QList<QPoint> Waypointlist;
    My_dragwidget * tower_selsect[3]={NULL};
    int money=1000;

signals:
    void back_to_choose();
};

#endif // GAMEWINDOW_H
