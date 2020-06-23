#include "bullet.h"
#include <QPropertyAnimation>
#include <QList>
Bullet::Bullet(QPoint start,QPoint end,QString filename,Enermy *enemy,int damage,gamewindow *window,int dur,QSize size)
{
 startpos=start;
 targetpos=end;
 pixmap=filename;
 target_enemy=enemy;
 game=window;
 this->damage=damage;
 if(size!=QSize(-1,-1))
     pixmap=pixmap.scaled(size);
 duration=dur;
}
void Bullet::move()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "currentpos");
        animation->setDuration(duration);
        animation->setStartValue(startpos);
        animation->setEndValue(targetpos);
        connect(animation,&QPropertyAnimation::finished, this, &Bullet::hitTarget);
        animation->start();

}
void Bullet::hitTarget()
{
    // 这样处理的原因是:
    // 可能多个炮弹击中敌人,而其中一个将其消灭,导致敌人delete
    // 后续炮弹再攻击到的敌人就是无效内存区域
    // 因此先判断下敌人是否还有效
    if(game->EnemyList().indexOf(target_enemy) != -1)
        target_enemy->getDamage(damage);
    game->removeBullet(this);

}
QPoint Bullet::getCurrentpos()
{
    return currentpos;
}
void Bullet::setCurrentpos(QPoint pos)
{
    currentpos=pos;
}
 void Bullet::draw(QPainter *painter)
 {

     painter->drawPixmap(currentpos,pixmap);
 }



 //派生减速子弹
 SlowBullet::SlowBullet(double _slowrate,QPoint start,QPoint end,QString filename,Enermy *enemy,int damage,gamewindow *window,int dur,QSize size)
     :Bullet(start,end,filename,enemy,damage,window,dur,size),slowrate(_slowrate)
 {

 }

 void SlowBullet::hitTarget()
 {
     // 这样处理的原因是:
     // 可能多个炮弹击中敌人,而其中一个将其消灭,导致敌人delete
     // 后续炮弹再攻击到的敌人就是无效内存区域
     // 因此先判断下敌人是否还有效
     if(game->EnemyList().indexOf(target_enemy) != -1)
     {
         target_enemy->getDamage(damage);
         target_enemy->getslow(slowrate);//减速效果
     }


     game->removeBullet(this);

 }
