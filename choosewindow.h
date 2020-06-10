#ifndef CHOOSEWINDOW_H
#define CHOOSEWINDOW_H

#include <QMainWindow>
#include <gamewindow.h>
namespace Ui {
class choosewindow;
}

class choosewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit choosewindow(QWidget *parent = 0);
    ~choosewindow();
    void paintEvent(QPaintEvent *event);
    gamewindow * newgame=NULL;
private:
    Ui::choosewindow *ui;
signals:
    void back_to_menu();

};

#endif // CHOOSEWINDOW_H
