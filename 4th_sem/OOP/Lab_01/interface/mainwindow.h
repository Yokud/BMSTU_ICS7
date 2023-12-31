#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logic/model/manager.h"

#define WIDTH 500
#define HEIGHT 500
#define READ_PATH "../Lab_01/data/mymodel.txt"
#define WRITE_PATH "../Lab_01/data/outmodel.txt"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    screen_params_t screen_sizes;
    void paintEvent(QPaintEvent *event);
    void print_error(QString message);
public slots:
    void scale_slot_handle();
    void rotate_slot_handle();
    void read_slot_handle();
    void write_slot_handle();
    void ask_slot_handle();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
