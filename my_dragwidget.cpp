#include "my_dragwidget.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
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
    return QWidget::mouseMoveEvent(event);
}
void My_dragwidget::mouseReleaseEvent(QMouseEvent *event)
{
        releasepoint=QPoint(pos().x()+width()/2,pos().y()+height()/2);
        qDebug()<<showpos();
        move(setPosition);
        emit want_to_set_tower();
        event->accept();
        return QWidget::mouseReleaseEvent(event);
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
