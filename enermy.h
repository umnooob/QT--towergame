#ifndef ENERMY_H
#define ENERMY_H
#include <QPoint>
#include <QPixmap>
#include <QMainWindow>
#include <dataconfig.h>
#include <QPainter>
#include <QObject>

bool collisionWithCircle(QPoint point1, int radius1, QPoint point2, int radius2);
class Enermy:public QObject
{
    Q_OBJECT
public:
    Enermy(int level,QString,QSize size=QSize(-1,-1));

    void loadwaypoint(int level);
    void draw(QPainter * );
    void move();
//    QPoint center();
protected:
bool Can_move=false;
int max_Hp=1000;
int currrent_Hp;
int walkingspeed=1;
QPoint position;
QPixmap pixmap;
int target;
double rotation;
QList<QPoint> Waypointlist;
//QMainWindow *game;

signals:
    void getHPdamage();
    void remove_enemy();
public slots:
    void doActivate();
};

#endif // ENERMY_H
