#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <my_pushbutton.h>
#include <QPainter>
#include <QPoint>
#include <QImage>
#include <QPixmap>
#include <QTimer>
#include <choosewindow.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cw=new choosewindow;//new a choose window
    My_pushbutton *start=new My_pushbutton(":/temstart.png");
    start->setParent(this);
    start->move(width()*0.5-120,height()*0.5-start->height());
    connect(start,My_pushbutton::clicked,[=](){
        start->zoom1();
        start->zoom2();
        QTimer::singleShot(500,this,[=](){
            cw->show();
            this->hide();
        });
    });
    connect(cw,&choosewindow::back_to_menu,[=](){
        this->show();
        cw->hide();
    });
}
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),QPixmap(":/grassmap.jpg"));

}

MainWindow::~MainWindow()
{
    delete ui;
}
