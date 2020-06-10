#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPushButton>
//塔的最大等级
const int maxtowerlevel=3;

class tower : public QObject
{
    Q_OBJECT
public:
    bool ispress=false;//是否按压
    static int radis_level[maxtowerlevel+1];//根据塔等级的攻击范围
    static int damage_level[maxtowerlevel+1];
    static int attackspeedrate_level[maxtowerlevel+1];
    int level=1;//塔的等级

    tower(QPoint ,QString ,QSize size=QSize(-1,-1),QString _towername="basetower");
   void show_area(QPainter *,int towerlevel);
   void draw(QPainter *);
//   void levelup();//升级

   QPoint printpos();
protected:
    int damage=damage_level[1];//伤害量 默认是一级
    int attackspeedrate=attackspeedrate_level[1];//单位是ms
    QString tower_name;
    QPoint pos;
    QPixmap pixmap;
signals:

public slots:
};

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

#endif // TOWER_H
