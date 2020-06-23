#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QPainter>
#include <my_pushbutton.h>
#include <QTimer>
#include <dataconfig.h>
#include <QDebug>
#include <QFont>
#include "tower.h"
#include "enermy.h"
#include "bullet.h"
#include <QFont>
gamewindow::gamewindow(int level):levelindex(level),ui(new Ui::gamewindow)
{
    ui->setupUi(this);
    
    setWindowTitle(QString("towergame level%1").arg(levelindex));



    QTimer *timer=new QTimer();
     QTimer *stander_timer=new QTimer();
     stander_timer->start(1000);
    timer->start(30);


    connect(timer,&QTimer::timeout, this, [=](){
        updateMap();
    });

    My_pushbutton * backbutton=new My_pushbutton(":/temback.jpg","",QSize(60,60));
    backbutton->move(width()*0.9,height()*0.9);
    backbutton->setParent(this);
    connect(backbutton,My_pushbutton::clicked,[=](){
        backbutton->zoom1();
        backbutton->zoom2();
        QTimer::singleShot(400,this,[=](){
           emit back_to_choose();
        });
      });
    My_pushbutton * stopbutton=new My_pushbutton(":/stop","",QSize(60,60));
    stopbutton->move(width()*0.9+60,height()*0.9);
    stopbutton->setParent(this);
    connect(stopbutton,My_pushbutton::clicked,[=](){
        stopbutton->zoom1();
        stopbutton->zoom2();
          static bool press=false;
          press=!press;
          if(press)
          {
              timer->stop();
              stop();
          }
          else
          {
              timer->start(30);
              start();
          }
      });
    tower_selsect[0]=new My_dragwidget(":/tower-base",QSize(60,60));
    tower_selsect[0]->setParent(this);
    tower_selsect[0]->setpos(QPoint(ui->gamearea->width()+ui->explainarea->width()*0.5,ui->explainarea->height()*0.8));
        connect(tower_selsect[0],&My_dragwidget::want_to_set_tower,[=](){
            if(canplacetower(tower_selsect[0]->showpos()))
                buildtower("tower-base",tower_selsect[0]->showpos());
        });
     tower_selsect[1]=new My_dragwidget(":/slowtower",QSize(60,60));
     tower_selsect[1]->setParent(this);
     tower_selsect[1]->setpos(QPoint(ui->gamearea->width()+ui->explainarea->width()*0.7,ui->explainarea->height()*0.8));
          connect(tower_selsect[1],&My_dragwidget::want_to_set_tower,[=](){
             if(canplacetower(tower_selsect[1]->showpos()))
                  buildtower("slowtower",tower_selsect[1]->showpos());
        });



     QFont font( "Microsoft YaHei", 10, 75);
    ui->moneylabel->setFont(font);
    ui->moneylabel->setStyleSheet(QString("border-image:url(:/background);color:red;"));
    ui->HPlabel->setFont(font);
    ui->HPlabel->setStyleSheet(QString("border-image:url(:/background);color:red;"));


     showtower=new show_message(QSize(ui->explainarea->size().width(),ui->explainarea->size().height()/2),this);
     showtower->setParent(ui->explainarea);
     showtower->move(0,0);


    //加载塔的位置
    loadtowerposition();
    //加载第一波兵线

    loadWave();

}
//建塔
void gamewindow::buildtower(QString name,QPoint pos)
{

    if(name=="tower-base")
    {
        auto it=towerposlist.begin();
        while (it!=towerposlist.end()) {
            if(it->contain_towerposition(pos))
            {
                QString filename=QString(":/%1").arg(name);
                tower *onetower=new tower(it->centerPos(),filename,this,QSize(50,50));
                //判断能不能购买塔
                if(money>=onetower->money_for_buildtower())
                    money-=onetower->money_for_buildtower();
                else
                {
                    delete onetower;
                    return;
                }

                Towerlist.push_back(onetower);
                qDebug()<<"set a tower";
                it->has_tower=true;
                update();
                return;
            }
            it++;
        }
    }
   else if(name=="slowtower")
    {
        auto it=towerposlist.begin();
        while (it!=towerposlist.end()) {
            if(it->contain_towerposition(pos))
            {
                QString filename=QString(":/%1").arg(name);
                tower *onetower=new slowtower(it->centerPos(),filename,this,QSize(50,50));
                //判断能不能购买塔
                if(money>=onetower->money_for_buildtower())
                    money-=onetower->money_for_buildtower();
                else
                {
                    delete onetower;
                    return;
                }

                Towerlist.push_back(onetower);
                qDebug()<<"set a slowtower";
                it->has_tower=true;
                update();
                return;
            }
            it++;
        }
    }
}
//能否放下塔
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
//绘画事件
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
        tower->show_area(&painter);
    }
    foreach (Enermy *enemy, Enemylist)
            enemy->draw(&painter);
    foreach (Bullet *bullet, Bulletlist) {
        bullet->draw(&painter);
    }


}

//塔的位置加载
void gamewindow::loadtowerposition()
{
    dataconfig data;
    for(int i=0;i<data.mdata[levelindex].size();i++)
        towerposlist.push_back(data.mdata[levelindex][i]);

}

//析构函数
gamewindow::~gamewindow()
{
    delete ui;
    towerposlist.clear();
    qDeleteAll(Towerlist);
    Towerlist.clear();
    qDeleteAll(Bulletlist);
    Bulletlist.clear();
    qDeleteAll(Enemylist);
    Enemylist.clear();
    delete [] tower_selsect;
    delete showtower;
}
//鼠标按压事件
void gamewindow::mousePressEvent(QMouseEvent *event)
{
    QString str=QString("X: %1 Y:%2").arg(event->x()).arg(event->y());
    qDebug()<<str;

    QPoint pressPos = event->pos();
    auto it=towerposlist.begin();
    while (it!=towerposlist.end()) {

        if(it->contain_towerposition(pressPos)&&it->hasTower())
        {
            foreach (tower *_tower, Towerlist)
            {

                if(_tower->printpos()==it->centerPos())
                {
                    _tower->ispress=!_tower->ispress;
                    update();
                    showtower->changeEnemy(_tower);
                }
                else
                     _tower->ispress=false;
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
//兵线加载
bool gamewindow::loadWave()
{

    if (waves >= 6)
            return false;
        int enemyStartInterval[] = { 100, 1000, 3000, 6000 };
        for (int i = 0; i < 4; ++i)
        {
            Enermy *enemy = new Enermy(levelindex,":/RO1",this,QSize(50,50));
            Enemylist.push_back(enemy);
            QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
        }
        return true;

}
//地图更新
void gamewindow::updateMap()
{
    //判断是否游戏结束
//    if(gameWin)
//        emit YOU_WIN_GAME();
//    else if(gameLose)
//        emit YOU_LOSE_GAME();
//else
//    {
        foreach (Enermy *enemy, Enemylist)
        {
            enemy->move();

        }
        foreach (tower *_tower, Towerlist) {
           _tower->checkEnemyInRange();
        }
          ui->moneylabel->setText(QString("金钱：%1").arg(money));
          ui->HPlabel->setText(QString("基地血量：%1").arg(HP));
        update();
//    }

}
//把敌人去除
void gamewindow::removeEnemy(Enermy *enemy)
{
    Q_ASSERT(enemy);
    Enemylist.removeOne(enemy);
    delete enemy;
    qDebug()<<"remove enemy called";
    if (Enemylist.empty())
    {
        ++waves; // 当前波数加1
        // 继续读取下一波
        if (!loadWave())
        {
            // 当没有下一波时，这里表示游戏胜利
            // 设置游戏胜利标志为true
            gameWin = true;
            // 游戏胜利转到游戏胜利场景

        }
    }
}
//基地血量减少
void gamewindow::gethomeHpDamage(int damage)
{
    if(HP>0)
    HP-=damage;
    if(HP<=0)
        gameLose=true;
}
//子弹去除
void gamewindow::removeBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);
    Bulletlist.removeOne(bullet);
    delete bullet;
}
//子弹增加
void gamewindow::addBullet(Bullet *bullet)
{
   Q_ASSERT(bullet);
    Bulletlist.push_back(bullet);
}
QList<Enermy*> gamewindow::EnemyList() const
{
    return Enemylist;
}
//金币增加
void gamewindow::get_awarded(int money)
{
    this->money+=money;
}
//摧毁塔
void gamewindow::destroy_tower(tower *_tower)
{
    auto it=towerposlist.begin();
    while (it!=towerposlist.end()) {

        if(it->hasTower())
        {

                if(_tower->printpos()==it->centerPos())
                {
                    it->has_tower=false;
                    break;
                }
        }
        it++;
    }
    Towerlist.removeOne(_tower);
    delete _tower;

}
//升级
void gamewindow::uplevel(tower *tower)
{
    if(money>=tower->money_for_levelup()&&tower->level<maxtowerlevel)
    {
        money-=tower->money_for_levelup();
        tower->level_up();
    }
}
//暂停按钮相关
void gamewindow::stop()
{
    foreach (tower *_tower, Towerlist) {
       _tower->stop();
    }
}
void gamewindow::start()
{
    foreach (tower *_tower, Towerlist) {
       _tower->continue_before();
    }
}
