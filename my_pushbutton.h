#ifndef MY_PUSHBUTTON_H
#define MY_PUSHBUTTON_H
#include <QPainter>
#include <QWidget>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <dataconfig.h>
#include <QLabel>
#include <QDialog>
#include <QTimer>
#include "tower.h"
#include "gamewindow.h"
class tower;
class gamewindow;
class QPushButton;
class QLabel;
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



//class showlabel:public QWidget
//{
//     Q_OBJECT
//public:
//    showlabel(QString,QSize size);

//};
class show_message:public QWidget
{
    Q_OBJECT
   public:
    show_message(QSize,gamewindow *);
    void changeEnemy(tower *);
   void paintEvent(QPaintEvent *event);
   ~show_message();
private:
    QLabel *towerimage;
    QLabel *towerlevel;
    QLabel *towername;
    My_pushbutton *levelup;
    My_pushbutton *destroy;
    gamewindow *game;
};

#endif // MY_PUSHBUTTON_H
