#ifndef MY_DRAGWIDGET_H
#define MY_DRAGWIDGET_H

#include <QWidget>
class My_dragwidget :public QWidget
{
    Q_OBJECT
public:
        My_dragwidget(QString ,QSize temsize=QSize(-1,-1));
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        void paintEvent(QPaintEvent *);
        QPoint showpos();
        void setpos(QPoint pos);
private:
   QPoint dragPosition;
   QPoint setPosition;
   QPoint releasepoint;
   QSize size;
   QPixmap pixmap;
signals:
   void want_to_set_tower();
};


#endif // MY_DRAGWIDGET_H
