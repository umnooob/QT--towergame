#include "gamewindialog.h"
#include "ui_gamewindialog.h"

GameWinDialog::GameWinDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWinDialog)
{
    ui->setupUi(this);
}

GameWinDialog::~GameWinDialog()
{
    delete ui;
}
