#ifndef ENERMY_H
#define ENERMY_H
#include <QPoint>
#include <QPixmap>
#include "gamewindow.h"
#include <dataconfig.h>
#include <QPainter>
#include <QObject>
#include "tower.h"
class gamewindow;
class tower;
 bool collisionWithCircle(QPoint point1, int radius1, QPoint point2, int radius2);
class Enermy:public QObject
{
    Q_OBJECT
public:
    Enermy(int level,QString,gamewindow *,QSize size=QSize(-1,-1));
//    ~Enermy();
    void loadwaypoint(int level);
    void draw(QPainter * );
    void move();
    void getDamage(int damage);
    QPoint centerpos()const;
    void getRemoved();
    void getAttacked(tower *attacker);
    void gotLostSight(tower *attacker);
    void getslow(double _slowrate);
protected:
int money;
bool Can_move=false;
int max_Hp=1000;
int currrent_Hp;
int walkingspeed=2;
QPoint position;
QPixmap pixmap;
int target;
double rotation;
QList<QPoint> Waypointlist;
//QPoint centerposition;
gamewindow *game;
QList<tower *>attack_towerlist;
double slowrate=1;
QTimer *timer;
signals:



public slots:
void doActivate();

};

#endif // ENERMY_H
