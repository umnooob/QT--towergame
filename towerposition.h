#ifndef TOWERPOSITION_H
#define TOWERPOSITION_H
#include <QSize>
#include <QPixmap>

class towerposition
{

public:

    towerposition(QPoint ,QString ,QSize size=QSize(-1,-1));
    towerposition();
    towerposition(const towerposition &tpos );
    towerposition & operator =(const towerposition &tpos );
    bool contain_towerposition(const QPoint &pos);//判断某点是否在towerposition内
    const QPoint centerPos() const;//towerposition的中心位置
    bool hasTower() const;

    QPoint pos;
    QPixmap pixmap;
    bool has_tower=false;
    QSize picture_size;
};

#endif // TOWERPOSITION_H
