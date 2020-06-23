#include "enermy.h"
#include <QVector2D>
#include <qmath.h>
#include <QDebug>
#include <QTimer>
   Enermy::Enermy(int level,QString filename,gamewindow *_game,QSize size)
{
    pixmap=filename;
    if(size!=QSize(-1,-1))
        pixmap=pixmap.scaled(size);
    loadwaypoint(level);
    game=_game;
    currrent_Hp=max_Hp;
    target=1;
    position=Waypointlist[0];
    rotation=0;
    money=100;
    timer=new QTimer;
    connect(timer,&QTimer::timeout,this,[=](){
        slowrate=1;
       timer->stop();
    });

}
// Enermy::~Enermy()
//   {

//       attack_towerlist.clear();
//       Waypointlist.clear();
//   }

 void Enermy::loadwaypoint(int level)
 {
     dataconfig data;
     for(int i=0;i<data.waypoint[level].size();i++)
         Waypointlist.push_back(data.waypoint[level][i]);
 }
 void Enermy::draw(QPainter *painter)
 {

      Q_ASSERT(this);
     if (!Can_move)
         return;
     // 血条的长度
     // 其实就是2个方框,红色方框表示总生命,固定大小不变
     // 绿色方框表示当前生命,受m_currentHp / m_maxHp的变化影响
      painter->save();
      static const QPoint offsetPoint(-pixmap.width() / 2, -pixmap.height() / 2);
      // 绘制炮塔并选择炮塔
      // 这里将坐标原点移到pos,绘制的适合,就要加上那个偏移点到左上角
      painter->translate(position);
      painter->drawPixmap(offsetPoint, pixmap);
     static const int Health_Bar_Width = pixmap.width();

     QPoint healthBarPoint = offsetPoint+ QPoint(0, -pixmap.height()/10);
     // 绘制血条
     painter->setPen(Qt::NoPen);
     painter->setBrush(Qt::red);
     QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 2));
     painter->drawRect(healthBarBackRect);
     painter->setBrush(Qt::green);
//     qDebug()<<currrent_Hp;
     QRect healthBarRect(healthBarPoint, QSize((double) currrent_Hp / max_Hp * Health_Bar_Width, 2));
     painter->drawRect(healthBarRect);
     // 绘制偏转坐标,由中心+偏移=左上


     // 绘制敌人


     painter->restore();
 }
 void Enermy::move()
 {
     if (!Can_move)
         return;
     if (collisionWithCircle(position, 1, Waypointlist[target], 1))
     {
         // 敌人抵达了一个航点
         if (target+1<Waypointlist.size())
         {
             // 还有下一个航点
             position = Waypointlist[target++];
         }
         else
         {
             // 表示进入基地
           game->gethomeHpDamage(1);
           game->removeEnemy(this);
             return;
         }
     }
     // 还在前往航点的路上
     // 目标航点的坐标
     QPoint targetPoint = Waypointlist[target];
     // 未来修改这个可以添加移动状态,加快,减慢,walkingSpeed是基准值
     // 向量标准化
     double movementSpeed = walkingspeed*slowrate;
     QVector2D normalized(targetPoint - position);
     normalized.normalize();
     position = position + normalized.toPoint() * movementSpeed;
     // 确定敌人选择方向
     // 默认图片向左,需要修正180度转右
     rotation = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) ;
//     centerposition=QPoint(position.x()+pixmap.width()/2,position.y()+pixmap.height()/2);
 }
 bool collisionWithCircle(QPoint point1, int radius1, QPoint point2, int radius2)
 {
     int xdif = point1.x() - point2.x();
     int ydif = point1.y() - point2.y();
     int distance = qSqrt(xdif * xdif + ydif * ydif);
     if (distance <= radius1 + radius2)
         return true;
     return false;
 }
void Enermy::doActivate()
{
    Can_move=true;
}
void Enermy::getDamage(int damage)
{


    currrent_Hp-=damage;
    if(currrent_Hp<=0)
    {
        currrent_Hp=0;
        qDebug()<<"one enemy die";

        game->get_awarded(money);
         getRemoved();
    }
}
QPoint Enermy::centerpos()const
{
    return position;
}

void Enermy::getRemoved()
{
    if (attack_towerlist.empty())
        return;
//    qDebug()<<"become remove";
    foreach (tower *attacker, attack_towerlist)
        attacker->targetKilled();

    game->removeEnemy(this);
}

void Enermy::getAttacked(tower *attacker)
{
    attack_towerlist.push_back(attacker);
}

void Enermy::gotLostSight(tower *attacker)
{
    attack_towerlist.removeOne(attacker);
}
void Enermy::getslow(double _slowrate)
{
    slowrate=_slowrate;
//    200ms restore
    timer->start(200);
}
