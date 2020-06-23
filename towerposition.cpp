#include "towerposition.h"

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
