#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dt = new DiceRollTracker(this);
    diceRoll = new DiceRollWidget(dt);

    setCentralWidget(diceRoll);
}

MainWindow::~MainWindow()
{
    delete ui;
}
