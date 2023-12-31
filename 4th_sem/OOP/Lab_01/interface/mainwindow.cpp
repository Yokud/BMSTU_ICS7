#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMessageBox>


void MainWindow::print_error(QString message)
{
    QMessageBox::critical(this, "Ошибка", message);
}

static double to_rad(double ang)
{
    double ret = ang * (M_PI / 180.0);
    return ret;
}

void MainWindow::scale_slot_handle()
{
    bool ok;
    double scale_x = ui->kx->text().toDouble(&ok);
    if (!ok || scale_x == 0)
    {
        print_error("Ошибка при чтении кэоффициента масштабирования по оси X");
        return;
    }

    double scale_y =  ui->ky->text().toDouble(&ok);
    if (!ok || scale_y == 0)
    {
        print_error("Ошибка при чтении кэоффициента масштабирования по оси Y");
        return;
    }

    double scale_z =  ui->kz->text().toDouble(&ok);
    if (!ok || scale_z == 0)
    {
        print_error("Ошибка при чтении кэоффициента масштабирования по оси Z");
        return;
    }

    params_t params;
    params.scale_params = {scale_x, scale_y, scale_z};
    task_t task = SCALE;
    model2D_t model;
    error_t err = manager(model, params, task);
    if (err == MODEL_VOID_ERROR)
    {
        print_error("Модель ещё не загружена");
        return;
    }
    repaint();
}

void MainWindow::rotate_slot_handle()
{
    bool ok;
    double angle =  ui->angle->text().toDouble(&ok);
    if (!ok)
    {
        print_error("Ошибка при чтении угла поворота");
        return;
    }
    QString axis_s = ui->axis->text();
    if (QString::compare(axis_s, "x", Qt::CaseInsensitive) &&
            QString::compare(axis_s, "y", Qt::CaseInsensitive) &&
            QString::compare(axis_s, "z", Qt::CaseInsensitive))
    {
        print_error("Ошибка при чтении оси поворота");
        return;
    }

    axis_t axis;
    if (!QString::compare(axis_s, "x", Qt::CaseInsensitive))
        axis = AXIS_X;
    else if (!QString::compare(axis_s, "y", Qt::CaseInsensitive))
        axis = AXIS_Y;
    else
        axis = AXIS_Z;

    params_t params;
    params.rotate_params = {to_rad(angle), axis};
    task_t task = ROTATE;
    model2D_t model;
    error_t err = manager(model, params, task);
    if (err == MODEL_VOID_ERROR)
    {
        print_error("Модель ещё не загружена");
        return;
    }
    repaint();
}

void MainWindow::read_slot_handle()
{
    params_t params;
    params.load_params = {READ_PATH};

    task_t task = READ;

    model2D_t model;
    error_t err = manager(model, params, task);

    if (err == MODEL_ALREADY_LOADED_ERROR)
    {
        print_error("Модель уже загружена");
        QMessageBox::StandardButton ans;
        ans = QMessageBox::question(this, "Загрузка новой модели", "Хотите загрузить новую модель?",
                                    QMessageBox::Yes | QMessageBox::No);
        if (ans == QMessageBox::Yes)
        {
            task = DESTROY;
            manager(model, params, task);

            MainWindow::read_slot_handle();
        }
        return;
    }
    else if (err == FILE_ERROR)
    {
        print_error("Ошибка во время чтения файла");
        return;
    }
    else if (err == READ_POINTS_ERROR)
    {
        print_error("Точки модели имеют неверный формат");
        return;
    }
    else if (err == MEMORY_ALLOCATION_ERROR)
    {
        print_error("Возникли ошибки при выделении памяти");
        return;
    }
    else if (err == READ_EDGES_ERROR)
    {
        print_error("Рёбра модели имеют неверный формат");
        return;
    }
    else if (err == INCORRECT_MODEL)
    {
        print_error("Некорректная модель");
        return;
    }

    repaint();
}

void MainWindow::write_slot_handle()
{
    params_t params;
    params.load_params = {WRITE_PATH};
    task_t task = WRITE;
    model2D_t model;
    error_t err = manager(model, params, task);
    if (err == MODEL_VOID_ERROR)
    {
        print_error("Модель ещё не загружена");
        return;
    }
    else if (err == FILE_ERROR)
    {
        print_error("Ошибка во время открытия файла");
        return;
    }
    repaint();
}

void MainWindow::ask_slot_handle()
{
    QString info = "Данная программа позволяет просматривать модели, состоящие из множества точек и рёбер, "
                   "масштабировать их и поворачивать по трём осям, а также сохранять результат преобразований "
                   "в текстовый файл.";

    QMessageBox::information(this, "Информация о программе", info);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    screen_sizes.screen_xmin = ui->groupBox->x();
    screen_sizes.screen_ymin = ui->groupBox->y();
    screen_sizes.screen_xmax = ui->groupBox->x() + ui->groupBox->width();
    screen_sizes.screen_ymax = ui->groupBox->y() + ui->groupBox->height();

    connect(ui->scaleButton, SIGNAL (clicked()), this, SLOT (scale_slot_handle()));

    connect(ui->rotateButton, SIGNAL (clicked()), this, SLOT (rotate_slot_handle()));

    connect(ui->readButton, SIGNAL (clicked()), this, SLOT (read_slot_handle()));

    connect(ui->writeButton, SIGNAL (clicked()), this, SLOT (write_slot_handle()));

    connect(ui->askButton, SIGNAL(clicked()), this, SLOT(ask_slot_handle()));
}

MainWindow::~MainWindow()
{
    params_t params;
    model2D_t model;
    task_t task = DESTROY;
    manager(model, params, task);
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter (this);
    Q_UNUSED(event);
    painter.setPen(Qt::red);
    params_t params;
    task_t task = PROJECTION;
    model2D_t model;
    params.proj_params.screen_params = screen_sizes;
    error_t err = manager(model, params, task);
    if (err == OK)
    {
        for (size_t i = 0; i < model.edges.n; i++)
        {
            painter.drawLine(
                    model.points2D.points_arr[model.edges.edges_arr[i].v1].x,
                    model.points2D.points_arr[model.edges.edges_arr[i].v1].y,
                    model.points2D.points_arr[model.edges.edges_arr[i].v2].x,
                    model.points2D.points_arr[model.edges.edges_arr[i].v2].y);
        }
        delete_edges(model.edges);
        delete_points2D(model.points2D);
    }
}
