#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <tower.h>
#include <QMainWindow>
#include <QList>
#include <QPaintEvent>
#include <choosewindow.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    choosewindow * cw;
//    void drawtowerpos(QList<const towerposition> &);
//    void show_area()
private:
    Ui::MainWindow *ui;
//    QList<towerposition> tower_pos;
};

#endif // MAINWINDOW_H
