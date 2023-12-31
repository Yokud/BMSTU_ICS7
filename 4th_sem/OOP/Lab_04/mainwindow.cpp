#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_1_clicked()
{
    lift.call(0);
}

void MainWindow::on_pushButton_2_clicked()
{
    lift.call(1);
}

void MainWindow::on_pushButton_3_clicked()
{
    lift.call(2);
}

void MainWindow::on_pushButton_4_clicked()
{
    lift.call(3);
}

void MainWindow::on_pushButton_5_clicked()
{
    lift.call(4);
}
