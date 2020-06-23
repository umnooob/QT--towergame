#ifndef DATACONFIG_H
#define DATACONFIG_H
#include <QMap>
#include <QVector>
#include <QPoint>
#include <towerposition.h>
class dataconfig
{
public:
    dataconfig();
    QMap <int,QVector<towerposition> > mdata;//存储塔的位置
    QMap <int,QVector<QPoint> > waypoint;//存储路径的拐点
};

#endif // DATACONFIG_H
