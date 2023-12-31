#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QMessageBox>
#include <QGraphicsScene>

#include "../facade/facade.h"
#include "../commands/command.h"
#include "../errors/errors.h"
#include "ui_mainwindow.h"
#include "../drawers/graphsfactory.h"
#include "configs/configs.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    const int win_x = 1001;
    const int win_y = 571;

    void update_scene();

    void clear_scene();

private slots:
    void on_move_button_clicked();

    void on_scale_button_clicked();

    void on_turn_button_clicked();

    void on_load_button_clicked();

    void on_add_camera_clicked();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<QGraphicsScene> scene;
    std::shared_ptr<Facade> facade;
    std::shared_ptr<BaseDrawer> drawer;
    std::shared_ptr<BaseLoader> loader;

    void registration();
    std::unique_ptr<AbsGraphFactory> createQtDrawerCreator();
};
#endif
