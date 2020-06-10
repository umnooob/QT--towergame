#include "enermy.h"
#include <QVector2D>
#include <qmath.h>
   Enermy::Enermy(int level,QString filename,QSize size)
{
    pixmap=filename;
    if(size!=QSize(-1,-1))
        pixmap=pixmap.scaled(size);
    loadwaypoint(level);
    currrent_Hp=max_Hp;
    target=1;
    position=Waypointlist[0];
    rotation=0;
}
 void Enermy::loadwaypoint(int level)
 {
     dataconfig data;
     for(int i=0;i<data.waypoint[level].size();i++)
         Waypointlist.push_back(data.waypoint[level][i]);
 }
 void Enermy::draw(QPainter *painter)
 {
     if (!Can_move)
         return;
     // 血条的长度
     // 其实就是2个方框,红色方框表示总生命,固定大小不变
     // 绿色方框表示当前生命,受m_currentHp / m_maxHp的变化影响
     static const int Health_Bar_Width = 50;
     painter->save();
     QPoint healthBarPoint = position + QPoint(0 , 0);
     // 绘制血条
     painter->setPen(Qt::NoPen);
     painter->setBrush(Qt::red);
     QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 2));
     painter->drawRect(healthBarBackRect);
     painter->setBrush(Qt::green);
     QRect healthBarRect(healthBarPoint, QSize((double) currrent_Hp / max_Hp * Health_Bar_Width, 2));
     painter->drawRect(healthBarRect);
     // 绘制偏转坐标,由中心+偏移=左上
     static const QPoint offsetPoint(pixmap.width() / 2, pixmap.height() / 2);
     painter->translate(position);
//     painter->rotate(rotation);
     // 绘制敌人
     painter->drawPixmap(offsetPoint, pixmap);
     painter->restore();
 }
 void Enermy::move()
 {
     if (!Can_move)
         return;
     if (collisionWithCircle(position, 1, Waypointlist[target], 1))
     {
         // 敌人抵达了一个航点
         if (target+1<=Waypointlist.size())
         {
             // 还有下一个航点
             position = Waypointlist[target++];
         }
         else
         {
             // 表示进入基地
           emit getHPdamage();
           emit remove_enemy();
             return;
         }
     }
     // 还在前往航点的路上
     // 目标航点的坐标
     QPoint targetPoint = Waypointlist[target];
     // 未来修改这个可以添加移动状态,加快,减慢,walkingSpeed是基准值
     // 向量标准化
     double movementSpeed = walkingspeed;
     QVector2D normalized(targetPoint - position);
     normalized.normalize();
     position = position + normalized.toPoint() * movementSpeed;
     // 确定敌人选择方向
     // 默认图片向左,需要修正180度转右
     rotation = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) ;
 }
 bool collisionWithCircle(QPoint point1, int radius1, QPoint point2, int radius2)
 {
     const int xdif = point1.x() - point2.x();
     const int ydif = point1.y() - point2.y();
     const int distance = qSqrt(xdif * xdif + ydif * ydif);
     if (distance <= radius1 + radius2)
         return true;
     return false;
 }
void Enermy::doActivate()
{
    Can_move=true;
}

