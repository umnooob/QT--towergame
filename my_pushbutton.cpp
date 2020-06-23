#include "my_pushbutton.h"
#include <QPixmap>
#include <QPropertyAnimation>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include<QtMath>
#include <QFont>
My_pushbutton::My_pushbutton(QString normalimg,QString pressimg,QSize size):Normalpath(normalimg),Presspath(pressimg)
{
    this->size=size;
    QPixmap pix;
    pix.load(Normalpath);
    if(size!=QSize(-1,-1))
        pix=pix.scaled(size);

    setFixedSize(pix.width(),pix.height());
    setIconSize(QSize(pix.width(),pix.height()));
    setIcon(pix);
    setStyleSheet("QPushButton{border:0px;}");
}
void My_pushbutton::zoom1()
{
    QPropertyAnimation *zoom=new QPropertyAnimation(this,"geometry");
    //时间
    zoom->setDuration(200);
    //起始位置
    zoom->setStartValue(QRect(x(),y(),width(),height()));
    zoom->setEndValue(QRect(x(),y()+5,width(),height()));
    zoom->setEasingCurve(QEasingCurve::OutBounce);
    zoom->start();
}
void My_pushbutton::zoom2()
{
    QPropertyAnimation *zoom=new QPropertyAnimation(this,"geometry");
    //时间
    zoom->setDuration(200);
    //起始位置
    zoom->setStartValue(QRect(x(),y()+5,width(),height()));
    zoom->setEndValue(QRect(x(),y(),width(),height()));
    zoom->setEasingCurve(QEasingCurve::OutBounce);
    zoom->start();
}
void My_pushbutton::mousePressEvent(QMouseEvent *e)
{
    if(Presspath!="")
    {
        QPixmap pix;
        pix.load(Presspath);
        if(size!=QSize(-1,-1))
            pix=pix.scaled(size);
        setFixedSize(pix.width(),pix.height());
        setIconSize(QSize(pix.width(),pix.height()));
        setIcon(pix);
        setStyleSheet("QPushButton{border:0px;}");
    }
    return QPushButton::mousePressEvent(e);
}

void My_pushbutton::mouseReleaseEvent(QMouseEvent *e)
{

    if(Presspath!="")
    {
        QPixmap pix;
        pix.load(Normalpath);
        if(size!=QSize(-1,-1))
            pix=pix.scaled(size);
        setFixedSize(pix.width(),pix.height());
        setIconSize(QSize(pix.width(),pix.height()));
        setIcon(pix);
        setStyleSheet("QPushButton{border:0px;}");
    }
    return QPushButton::mouseReleaseEvent(e);
}




//showanddisappear
show_message::show_message(QSize size,gamewindow *_game):game(_game)
{
    setFixedSize(size);
//    setStyleSheet(QString::fromUtf8("border:1px solid red"));

    towerimage=new QLabel;
    towerimage->setParent(this);
    towerimage->move(width()/2,20);
    towerimage->setFixedSize(width()/2,height()/2);
    QFont font( "Microsoft YaHei", 10, 75);

    towerlevel=new QLabel;
    towerlevel->setParent(this);
    towerlevel->move(20,20);
    towerlevel->setFixedWidth(width()/2);
    towerlevel->setFixedHeight(40);
    towerlevel->setFont(font);
    towerlevel->setStyleSheet(QString("color:red;"));

    towername=new QLabel;
    towername->setParent(this);
    towername->move(20,80);
    towername->setFixedSize(width()/2,40);
    towername->setFont(font);
    towername->setStyleSheet(QString("color:red;"));

    levelup=new My_pushbutton(":/levelup","",QSize(width()/4,height()/8));
    levelup->setParent(this);
    levelup->move(0,size.height()/4*3);



    destroy=new My_pushbutton(":/delete","",QSize(width()/4,height()/8));
    destroy->setParent(this);
    destroy->move(width()/2,height()/4*3);


}
show_message::~show_message()
{
    delete towerimage;
    delete towerlevel;
    delete towername;
    delete levelup;
    delete destroy;
}

void show_message::changeEnemy(tower *_tower)
{
        if(_tower->show_name()=="basetower")
        {
            towerimage->setPixmap(QPixmap(":/tower-base"));

        }
        else if(_tower->show_name()=="slowtower")
            towerimage->setPixmap(QPixmap(":/slowtower"));
        towername->setText(QString("Name: %1").arg(_tower->show_name()));
        towerlevel->setText(QString("Level: %1").arg(_tower->level));

        disconnect(levelup,0,0,0);
        disconnect(destroy,0,0,0);
        connect(levelup,My_pushbutton::clicked,[=](){

            game->uplevel(_tower);
            towerlevel->setText(QString("Level: %1").arg(_tower->level));
                levelup->zoom1();
                levelup->zoom2();
          });
        connect(destroy,My_pushbutton::clicked,[=](){
            destroy->zoom1();
            destroy->zoom2();
              game->destroy_tower(_tower);
              disconnect(levelup,0,0,0);
              disconnect(destroy,0,0,0);
          });
}
void show_message::paintEvent(QPaintEvent *event)
{
//    QPainterPath path;
//       path.setFillRule(Qt::WindingFill);
    //       path.addRect(10, 10, this->width()-20, this->height()-20);

    //       QPainter painter(this);
    //       painter.setRenderHint(QPainter::Antialiasing, true);
    //       painter.fillPath(path, QBrush(Qt::white));

//       QColor color(0, 0, 0, 50);
//       for(int i=0; i<10; i++)
//       {
//           QPainterPath path;
//           path.setFillRule(Qt::WindingFill);
//           path.addRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2);
//           color.setAlpha(150 - qSqrt(i)*50);
//           painter.setPen(color);
//           painter.drawPath(path);
//       }
}
