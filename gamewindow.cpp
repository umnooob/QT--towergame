#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QPainter>
#include <my_pushbutton.h>
#include <QTimer>
#include <dataconfig.h>
#include <QDebug>
#include <QFont>
gamewindow::gamewindow(int level):levelindex(level),ui(new Ui::gamewindow)
{
    ui->setupUi(this);
    
    setWindowTitle(QString("towergame level%1").arg(levelindex));
    My_pushbutton * backbutton=new My_pushbutton(":/temback.jpg","",QSize(30,30));
    QFont font;

    QTimer *timer=new QTimer();
     QTimer *stander_timer=new QTimer();
     stander_timer->start(1000);
    timer->start(30);


    connect(timer,&QTimer::timeout, this, [=](){
        updateMap();
    });
//    connect(timer,&QTimer::timeout,[=](){
//        ui->label->setText(QString("money: %1").arg(money));
//    });

    
    backbutton->move(width()*0.9,height()*0.9);
    backbutton->setParent(this);
    connect(backbutton,My_pushbutton::clicked,[=](){
        backbutton->zoom1();
        backbutton->zoom2();
        QTimer::singleShot(400,this,[=](){
           emit back_to_choose();
        });
      });

    
    tower_selsect[0]=new My_dragwidget(":tower-base.png",QSize(60,60));
    tower_selsect[0]->setParent(this);
    tower_selsect[0]->setpos(QPoint(ui->gamearea->width()+ui->explainarea->width()*0.5,ui->explainarea->height()*0.5));
        connect(tower_selsect[0],&My_dragwidget::want_to_set_tower,[=](){
            if(canplacetower(tower_selsect[0]->showpos()))
                buildtower("basetower",tower_selsect[0]->showpos());
        });

    //加载塔的位置
    loadtowerposition();
//    //加载路径拐点位置
//    loadwaypoint();
    loadWave();

}
void gamewindow::buildtower(QString name,QPoint pos)
{
    if(name=="basetower")
    {
        auto it=towerposlist.begin();
        while (it!=towerposlist.end()) {
            if(it->contain_towerposition(pos))
            {
                tower *onetower=new tower(it->centerPos(),":/tower-base",QSize(70,70));
                Towerlist.push_back(onetower);
                qDebug()<<"set a tower";
                it->has_tower=true;
                update();
                return;
            }
            it++;
        }

    }
}
bool gamewindow::canplacetower(QPoint point)
{
    auto it=towerposlist.begin();
    while (it!=towerposlist.end()) {
        if(it->contain_towerposition(point)&&!it->hasTower())
        {
            return true;
        }
        it++;
    }
    return false;
}

void gamewindow::paintEvent(QPaintEvent *event)
{
    //画背景
    QString level=QString(":/level%1.jpg").arg(levelindex);
    QPainter painter(this);
    painter.drawPixmap(0,0,ui->gamearea->width(),ui->gamearea->height(),QPixmap(level));
    painter.drawPixmap(ui->gamearea->width(),0,ui->explainarea->width(),ui->explainarea->height(),QPixmap(":/background.png"));
    //画塔位
    for(int i=0;i<towerposlist.size();i++)
    {
        if(!towerposlist[i].hasTower())
        painter.drawPixmap(towerposlist[i].pos,towerposlist[i].pixmap);
    }

    //画塔
    foreach (tower *tower, Towerlist)
    {
        tower->draw(&painter);
        if(tower->ispress)
        tower->show_area(&painter,tower->level);
    }
    foreach (Enermy *enemy, Enemylist)
            enemy->draw(&painter);


}


void gamewindow::loadtowerposition()
{
    dataconfig data;
    for(int i=0;i<data.mdata[levelindex].size();i++)
        towerposlist.push_back(data.mdata[levelindex][i]);

}


gamewindow::~gamewindow()
{
    delete ui;
}

void gamewindow::mousePressEvent(QMouseEvent *event)
{
    QString str=QString("X: %1 Y:%2").arg(event->x()).arg(event->y());
    qDebug()<<str;

    QPoint pressPos = event->pos();
    auto it=towerposlist.begin();
    while (it!=towerposlist.end()) {

        if(it->contain_towerposition(pressPos)&&it->hasTower())
        {
            foreach (tower *tower, Towerlist)
            {
                if(tower->printpos()==it->centerPos())
                {
                    tower->ispress=!tower->ispress;
                    update();
                }
            }
        }
//        if(it->contain_towerposition(pressPos)&&!it->hasTower())
//        {
//            qDebug()<<"set a tower";
//            it->has_tower=true;
//            money-=200;
//            QString str2=QString(":/tower-%1.png").arg("base");
//            tower *onetower=new tower(it->centerPos(),str2,QSize(70,70));
//            Towerlist.push_back(onetower);
//            update();
//            break;
//        }
        it++;
    }

}
bool gamewindow::loadWave()
{

    if (waves >= 6)
            return false;
        int enemyStartInterval[] = { 100, 500, 600, 1000, 3000, 6000 };
        for (int i = 0; i < 6; ++i)
        {
            Enermy *enemy = new Enermy(levelindex,":/RO1.png",QSize(50,50));
            Enemylist.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
        }
        return true;

}
void gamewindow::updateMap()
{
    foreach (Enermy *enemy, Enemylist)
            enemy->move();
    update();
}
