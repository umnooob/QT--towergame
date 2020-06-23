#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPushButton>
#include <QTimer>
#include "gamewindow.h"

#include <QList>
#include "enermy.h"
//塔的最大等级
const int maxtowerlevel=3;
class gamewindow;
class Enermy;
class QPainter;
class QTimer;
class tower : public QObject
{
    Q_OBJECT
public:
    bool ispress=false;//是否按压
    //派生类需修改属性
     int radis_level[maxtowerlevel+1];//根据塔等级的攻击范围
     int damage_level[maxtowerlevel+1];
     int attackspeedrate_level[maxtowerlevel+1];
     int money_level[maxtowerlevel+1];

    int level=1;//塔的等级

    tower(QPoint ,QString ,gamewindow *_game,QSize size=QSize(-1,-1),QString _towername="basetower");
//    virtual ~tower();
   void show_area(QPainter *);
   void draw(QPainter *);
   virtual void level_up();
    virtual void shoot();
    void attack_enemy();
    void choose_enemy(Enermy *enemy);
   QPoint printpos();
   void losesight();
//   bool contain(const QPoint );
//   bool has_chosen_enemy();
    void checkEnemyInRange();
    void targetKilled();
    int money_for_levelup()const;
    int money_for_buildtower()const;
    void stop();
    void continue_before();
    QString show_name()const;
protected:
    int damage;//伤害量 默认是一级
    int attackspeedrate;//单位是ms
    QString tower_name;
    QPoint pos;
    QPixmap pixmap;
    int radius;
    QTimer *firetimer;
    gamewindow *game;
    Enermy *chosen_enemy=NULL;
signals:

public slots:
};



class slowtower:public tower
{
public:
    slowtower(QPoint ,QString ,gamewindow *_game,QSize size=QSize(-1,-1),QString _towername="slowtower");
    void level_up();
    void shoot();
    double slowrate_level[maxtowerlevel+1];
protected:
    double slowrate;
};

#endif // TOWER_H
