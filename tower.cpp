#include "tower.h"
#include <QPainter>
#include <QPixmap>
#include <QPen>
#include <QDebug>
#include <QVector2D>
#include <QList>
//tower


tower::tower(QPoint _pos,QString filename,gamewindow *_game, QSize size,QString _towername)
{
    pos=_pos;pixmap=filename;tower_name=_towername;game=_game;
    if(size!=QSize(-1,-1))
        pixmap=pixmap.scaled(size);
    firetimer=new QTimer(this);
    connect(firetimer,&QTimer::timeout,this,&tower::shoot);
    //初始化
    int tradis[maxtowerlevel+1]={0,100,150,170};
    int tdamage[maxtowerlevel+1]={0,100,200,250};
    int tattackspeedrate[maxtowerlevel+1]={0,600,400,280};
    int  tmoney[maxtowerlevel+1]={0,300,100,100};
    for(int i=0;i<=maxtowerlevel;i++)
    {
        radis_level[i]=tradis[i];
        damage_level[i]=tdamage[i];
        attackspeedrate_level[i]=tattackspeedrate[i];
         money_level[i]=tmoney[i];
    }
    radius=radis_level[1];
    damage=damage_level[1];
    attackspeedrate=attackspeedrate_level[1];
}
//tower::~ tower()
//{
//    delete firetimer;
//}

void tower::draw(QPainter *painter)
{

    painter->save();
    static const QPoint offsetPoint(-pixmap.width() / 2, -pixmap.height() / 2);
    // 绘制炮塔并选择炮塔
    // 这里将坐标原点移到pos,绘制的适合,就要加上那个偏移点到左上角
    painter->translate(pos);
    painter->drawPixmap(offsetPoint, pixmap);
    painter->restore();
}

void tower::show_area(QPainter *painter)
{


    painter->save();
    QPen pen;
    pen.setColor(Qt::white);
    pen.setStyle(Qt::DotLine);
    painter->setPen(pen);
    painter->drawEllipse(pos,radius,radius);
    painter->restore();

}

QPoint tower::printpos()
{
    return pos;
}
void tower::level_up()
{
    if(level<maxtowerlevel)
        level++;
    damage=damage_level[level];
    attackspeedrate=attackspeedrate_level[level];
    radius=radis_level[level];
}
void tower::shoot()
{

         Bullet *bullet=new Bullet(pos,chosen_enemy->centerpos(),":/bullet",chosen_enemy,damage,game,100,QSize(20,20));
         qDebug()<<"a new bullet";
         bullet->move();
        game->addBullet(bullet);



}
void tower::attack_enemy()
{
    firetimer->start(attackspeedrate);
}
void tower::choose_enemy(Enermy *enemy)
{


        if(chosen_enemy==NULL)
        {
         chosen_enemy=enemy;
        chosen_enemy->getAttacked(this);
        attack_enemy();
        }

}
void tower::losesight()
{
    chosen_enemy->gotLostSight(this);
    if(chosen_enemy)
        chosen_enemy=NULL;
    firetimer->stop();
}
//bool tower::contain(const QPoint x)
//{
//    if((pos.x()-x.x())*(pos.x()-x.x())+(pos.y()-x.y())*(pos.y()-x.y())<=radius*radius)
//        return true;
//    return false;
//}
//bool tower::has_chosen_enemy()
//{
//    if(chosen_enemy==NULL)
//        return false;
//    return true;
//}
void tower::checkEnemyInRange()
{

    if (chosen_enemy!=NULL)
    {

//		// 这种情况下,需要旋转炮台对准敌人
//		// 向量标准化
//		QVector2D normalized(m_chooseEnemy->pos() - m_pos);
//		normalized.normalize();
//		m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) - 90;

        // 如果敌人脱离攻击范围
        if (!collisionWithCircle(pos, radius, chosen_enemy->centerpos(), 1))
            losesight();
    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内
//        qDebug()<<"begin choose";
        QList<Enermy *> enemyList = game->EnemyList();
        foreach (Enermy *enemy, enemyList)
        {
//            qDebug()<<"circle";
            if (collisionWithCircle(pos, radius, enemy->centerpos(), 1))
            {
                qDebug()<<"choose a enemy";
                choose_enemy(enemy);
                break;
            }
        }
    }
}
void tower::targetKilled()
{
    if (chosen_enemy)
        chosen_enemy = NULL;

    firetimer->stop();

}

int tower::money_for_levelup()const
{
    return money_level[level+1];
}

int tower::money_for_buildtower()const
{
    return money_level[1];
}

 QString tower::show_name()const
 {
     return tower_name;
 }
 void tower::stop()
 {
     firetimer->stop();
 }
 void tower::continue_before()
 {
     if(chosen_enemy)
         attack_enemy();
 }


 //派生的减速塔


 slowtower::slowtower(QPoint _pos,QString filename,gamewindow *_game,QSize size,QString _towername)
     :tower(_pos,filename,_game,size,_towername)
 {
     int tradis[maxtowerlevel+1]={0,80,100,120};
     int tdamage[maxtowerlevel+1]={0,50,70,80};
     int tattackspeedrate[maxtowerlevel+1]={0,450,330,280};
     int  tmoney[maxtowerlevel+1]={0,150,50,50};
     double tslowrate[maxtowerlevel+1]={0,0.35,0.45,0.5};
     for(int i=0;i<=maxtowerlevel;i++)
     {
         radis_level[i]=tradis[i];
         damage_level[i]=tdamage[i];
         attackspeedrate_level[i]=tattackspeedrate[i];
          money_level[i]=tmoney[i];
          slowrate_level[i]=tslowrate[i];
     }
     radius=radis_level[1];
     damage=damage_level[1];
     attackspeedrate=attackspeedrate_level[1];
     slowrate=slowrate_level[1];
 }

 void slowtower::level_up()
 {
     if(level<maxtowerlevel)
         level++;
     damage=damage_level[level];
     attackspeedrate=attackspeedrate_level[level];
     radius=radis_level[level];
     slowrate=slowrate_level[level];
 }
 void slowtower::shoot()
 {


     Bullet *bullet=new SlowBullet(slowrate,pos,chosen_enemy->centerpos(),":/slowbullet",chosen_enemy,damage,game,100,QSize(20,20));
          qDebug()<<"a new slowbullet";
          bullet->move();
         game->addBullet(bullet);
 }
