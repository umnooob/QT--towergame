#include "tower.h"
#include <QPainter>
#include <QPixmap>
#include <QPen>
//tower

int tower::radis_level[maxtowerlevel+1]={0,100,150,170};
int tower::damage_level[maxtowerlevel+1]={0,100,200,250};
int tower::attackspeedrate_level[maxtowerlevel+1]={0,1000,800,650};

tower::tower(QPoint _pos,QString filename,QSize size,QString _towername)
{
    pos=_pos;pixmap=filename;tower_name=_towername;
    if(size!=QSize(-1,-1))
        pixmap=pixmap.scaled(size);
}

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

void tower::show_area(QPainter *painter,int towerlevel)
{

    painter->save();
    QPen pen;
    pen.setColor(Qt::white);
    pen.setStyle(Qt::DotLine);
    painter->setPen(pen);
    painter->drawEllipse(pos,radis_level[towerlevel],radis_level[towerlevel]);
    painter->restore();

}

QPoint tower::printpos()
{
    return pos;
}




//towerposition


towerposition::towerposition()
{
}
towerposition::towerposition(QPoint _pos,QString filename,QSize size)
{
    pos=_pos;pixmap=QPixmap(filename);
    picture_size=pixmap.size();
    if(size!=QSize(-1,-1))
    {
       pixmap=pixmap.scaled(size);
       picture_size=size;
     }
}
towerposition::towerposition(const towerposition &tpos )
{
    pos=tpos.pos;pixmap=tpos.pixmap;picture_size=tpos.picture_size;has_tower=tpos.has_tower;
}
 towerposition & towerposition::operator =(const towerposition &tpos )
 {
     pos=tpos.pos;pixmap=tpos.pixmap;picture_size=tpos.picture_size;has_tower=tpos.has_tower;
     return *this;
 }
bool towerposition::contain_towerposition(const QPoint &pos)
{
    bool isXInHere = (this->pos.x() <= pos.x()) && (pos.x() <= (this->pos.x() +picture_size.width()));
    bool isYInHere = (this->pos.y() <= pos.y() )&& (pos.y() <= (this->pos.y() + picture_size.height()));
        return isXInHere && isYInHere;
}
const QPoint towerposition::centerPos() const
{
    QPoint offsetPoint(picture_size.width() / 2,picture_size.height() / 2);
    return pos + offsetPoint;
}

bool towerposition::hasTower() const
{
    return has_tower;
}
