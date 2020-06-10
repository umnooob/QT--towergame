#ifndef MY_PUSHBUTTON_H
#define MY_PUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <dataconfig.h>
class My_pushbutton : public QPushButton
{
    Q_OBJECT
public:
    //使用时如果不用变换图片，就不用补全pressimg
     My_pushbutton(QString normalimg,QString pressimg="",QSize size=QSize(-1,-1));
     void zoom1();
     void zoom2();
     void mousePressEvent(QMouseEvent *e);
     void mouseReleaseEvent(QMouseEvent *e);
private:
     QString Normalpath;
     QString Presspath;
     QSize size;
signals:

public slots:
};

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

#endif // MY_PUSHBUTTON_H
