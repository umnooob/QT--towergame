#include "dataconfig.h"
#include <QPoint>
#include <QVector>
dataconfig::dataconfig()
{

    QVector<towerposition> data;
    QPoint pos[] =
            {
                QPoint(260, 209),
                QPoint(500, 400),
                QPoint(694, 351),
                QPoint(85, 427),
                QPoint(500,540)

            };
            int len	= sizeof(pos) / sizeof(pos[0]);

            for (int i = 0; i < len; ++i)
                data.push_back(towerposition(pos[i],":/towerposition.png",QSize(70,70)));
     mdata.insert(1,data);

     data.clear();
     QPoint pos2[] =
             {
                 QPoint(252, 161),
                 QPoint(483, 286),
                 QPoint(684, 269),
                 QPoint(74, 346)

             };
             len= sizeof(pos2) / sizeof(pos2[0]);

             for (int i = 0; i < len; ++i)
                 data.push_back(towerposition(pos2[i],":/towerposition.png",QSize(70,70)));
      mdata.insert(2,data);







      QVector<QPoint> wp;
      QPoint wp1[] =
              {
          QPoint(0,355),
          QPoint(164, 355),
          QPoint(182, 173),
          QPoint(405, 167),
          QPoint(410, 486),
          QPoint(635, 486),
          QPoint(635, 305),
          QPoint(720, 300),
          QPoint(723, 188)

              };
              len	= sizeof(wp1) / sizeof(wp1[0]);

              for (int i = 0; i < len; ++i)
                  wp.push_back(wp1[i]);
       waypoint.insert(1,wp);
       wp.clear();

       QPoint wp2[] =
               {
           QPoint(0,283),
           QPoint(175, 266),
           QPoint(185, 142),
           QPoint(402, 126),
           QPoint(410, 367),
           QPoint(635, 369),
           QPoint(646, 238),
           QPoint(718, 227),
           QPoint(712, 141),

               };
               len	= sizeof(wp2) / sizeof(wp2[0]);

               for (int i = 0; i < len; ++i)
                   wp.push_back(wp2[i]);
        waypoint.insert(2,wp);



}
