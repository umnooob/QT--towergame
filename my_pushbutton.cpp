#include "my_pushbutton.h"
#include <QPixmap>
#include <QPropertyAnimation>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
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



My_dragwidget::My_dragwidget(QString filename,QSize temsize)
{
    pixmap=filename;
    size=pixmap.size();

    if(temsize!=QSize(-1,-1))
    {
        pixmap=pixmap.scaled(temsize);
        size=temsize;
    }
    setFixedSize(size);

}
void My_dragwidget::setpos(QPoint pos)
{
    setPosition=pos;move(setPosition);
}

void My_dragwidget::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton) //点击左边鼠标
    {
         dragPosition = event->globalPos() - frameGeometry().topLeft();
         //globalPos()获取根窗口的相对路径，frameGeometry().topLeft()获取主窗口左上角的位置
         event->accept();   //鼠标事件被系统接收
    }

}

void My_dragwidget::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons() == Qt::LeftButton) //当满足鼠标左键被点击时。
    {
         move(event->globalPos() - dragPosition);//移动窗口
         event->accept();
    }
}
void My_dragwidget::mouseReleaseEvent(QMouseEvent *event)
{
        releasepoint=QPoint(pos().x()+width()/2,pos().y()+height()/2);
        qDebug()<<showpos();
        move(setPosition);
        emit want_to_set_tower();
        event->accept();

}

void My_dragwidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);//创建一个QPainter对象
    painter.drawPixmap(0,0,size.width(),size.height(),QPixmap(pixmap));//绘制图片到窗口
    /*
      QPixmap(":/images/Watermelon.png")如果改为QPixmap()，则只能看到绘制出的框架，看不到图片颜色，也就是看不到图片。
    */
}
QPoint My_dragwidget::showpos()
{
    return releasepoint;
}
