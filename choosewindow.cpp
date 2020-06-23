#include "choosewindow.h"
#include "ui_choosewindow.h"
#include <my_pushbutton.h>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <gamewindow.h>
choosewindow::choosewindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::choosewindow)
{
    ui->setupUi(this);
    My_pushbutton * backbutton=new My_pushbutton(":/temback","",QSize(30,30));

    backbutton->move(width()*0.9,height()*0.9);
    backbutton->setParent(this);
    connect(backbutton,My_pushbutton::clicked,[=](){
        backbutton->zoom1();
        backbutton->zoom2();
        QTimer::singleShot(400,this,[=](){
           emit back_to_menu();
        });
      });

    for(int i=1;i<=maxlevel;i++)//布置选关按钮
    {
        QString level=QString(":/%1.png").arg(i);
        My_pushbutton *newlevel=new My_pushbutton(level);
        newlevel->setParent(this);
        newlevel->move(150*(i%4),150*(i/4)+150);

        connect(newlevel,My_pushbutton::clicked,[=](){
                if(newgame==NULL)
                    newgame=new gamewindow(i);

                 this->hide();
                 newgame->show();

                 connect(newgame,&gamewindow::back_to_choose,[=](){//返回后删除
                     newgame->hide();
                     this->show();
                     delete newgame;
                     newgame=NULL;
                 });
                 connect(newgame,&gamewindow::YOU_LOSE_GAME,[=](){
                     newgame->hide();
                     delete newgame;
                     newgame=NULL;

                 });
          });
    }

}
void choosewindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/grassmap.jpg"));
}

choosewindow::~choosewindow()
{
    delete ui;
}
