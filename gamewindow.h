#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

#include <QList>
#include <QDebug>
#include <QDrag>
#include <my_pushbutton.h>
#include "tower.h"
#include "enermy.h"
#include "bullet.h"
#include "my_dragwidget.h"
//设置最大关卡
const int maxlevel=2;
class show_message;
namespace Ui {
class gamewindow;
}
class Bullet;
class Enermy;
class tower;
class towerposition;
class gamewindow : public QMainWindow
{
    Q_OBJECT
public:
    int levelindex;
    int waves=0;
    gamewindow(int level);
    ~ gamewindow();
    void paintEvent(QPaintEvent *event);
    void loadtowerposition();
//    void loadwaypoint();
    void mousePressEvent(QMouseEvent *event);

    bool canplacetower(QPoint);
    void buildtower(QString ,QPoint);

    bool loadWave();
    void updateMap();
    void removeEnemy(Enermy *enemy);
    void gethomeHpDamage(int damage);
    void removeBullet(Bullet *bullet);
    void addBullet(Bullet *bullet);
    QList<Enermy *> EnemyList() const;
    void get_awarded(int money);
    void destroy_tower(tower *_tower);
   void uplevel(tower *tower);
   void stop();
   void start();
private:
    Ui::gamewindow *ui;
    QList<towerposition> towerposlist;
    QList<tower *> Towerlist;
    QList<Bullet *>Bulletlist;
    QList<Enermy *> Enemylist;
//    QList<QPoint> Waypointlist;
    My_dragwidget * tower_selsect[3]={NULL};
    show_message* showtower;
    int money=1000;
    bool gameWin=false;
    bool gameLose=false;
    int HP=5;

signals:
    void back_to_choose();
    void YOU_WIN_GAME();
    void YOU_LOSE_GAME();
};

#endif // GAMEWINDOW_H
