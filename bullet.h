#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QSize>
#include <enermy.h>
#include <QPainter>
#include "gamewindow.h"
class gamewindow;
class Enermy;
class Bullet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint currentpos READ getCurrentpos WRITE setCurrentpos)
public:

     Bullet(QPoint ,QPoint,QString ,Enermy *,int ,gamewindow *,int dur=100,QSize size=QSize(-1,-1));
     void move();
     virtual void hitTarget();
     QPoint getCurrentpos();
     void draw(QPainter *);
     void setCurrentpos(QPoint pos);

protected:
   QPoint  startpos;
   QPoint targetpos;
   QPoint currentpos;
   int damage=100;
   QPixmap pixmap;
   int duration;
    Enermy *target_enemy;
    gamewindow *game;
signals:

public slots:
};


class SlowBullet:public Bullet
{
public:
    SlowBullet(double,QPoint ,QPoint,QString ,Enermy *,int ,gamewindow *,int dur=100,QSize size=QSize(-1,-1));
    void hitTarget();
 protected:
    double slowrate;
};

#endif // BULLET_H
