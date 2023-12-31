#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->registration();
    ui->graphicsView->setScene(scene.get());
    std::shared_ptr<FacadeCreator> cr(new ConFacadeCreator());
    this->facade = cr->getFacade();

    SetCommand com(std::make_shared<Camera>());
    facade->run(com);
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::unique_ptr<AbsGraphFactory> MainWindow::createQtDrawerCreator()
{
    scene = std::shared_ptr<QGraphicsScene>(new QGraphicsScene());
    std::shared_ptr<QPen> pen (new QPen(Qt::red));
    std::shared_ptr<QBrush> brush (new QBrush(Qt::white));

    return std::unique_ptr<AbsGraphFactory>(new QtFactory(scene, pen, brush));
}

void MainWindow::registration()
{
    std::string configName = "C:\\msys64\\home\\Yokud\\4_sem_SE\\OOP\\Lab_03\\data\\config.txt";

    GraphLibConfig conf(configName);
    conf.readConfig();
    std::string ls = conf.getLoadSource();
    std::string fr = conf.getFrame();

    GraphSolution graphicsSolution;
    graphicsSolution.registration("qt", &MainWindow::createQtDrawerCreator);

    std::shared_ptr<AbsGraphFactory>factory(graphicsSolution.create(this, fr));
    drawer = factory->createGraphics();

    if (ls != "file")
    {
        std::string s = "Неизвестный загрузчик";
        throw FileError(s);
    }

    loader = std::make_shared<FileLoader>();
}


void MainWindow::on_move_button_clicked()
{
    try
    {
        double x = ui->dx_box->value();
        double y = ui->dy_box->value();
        double z = ui->dz_box->value();

        std::shared_ptr<ReformManager> rm(new ReformManager());

        ReformCommand move_command(rm, 0, Point(x, y, z), Point(1, 1, 1), Point(0, 0, 0));
        facade->run(move_command);
        update_scene();
    } catch (const ModelError &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной модели");
        return;
    }
}

void MainWindow::on_scale_button_clicked()
{
    try
    {
        double x = ui->kx_box->value();
        double y = ui->ky_box->value();
        double z = ui->kz_box->value();

        std::shared_ptr<ReformManager> rm(new ReformManager());
        ReformCommand scale_command(rm, 0, Point(0, 0, 0), Point(x, y, z), Point(0, 0, 0));

        facade->run(scale_command);
        update_scene();
    } catch (const CameraError &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной камеры.");
        return;
    } catch (const ModelError &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной модели");
        return;
    }
}

void MainWindow::on_turn_button_clicked()
{
    try
    {
        double x = ui->ox_box->value();
        double y = ui->oy_box->value();
        double z = ui->oz_box->value();

        std::shared_ptr<ReformManager> rm(new ReformManager());
        ReformCommand scale_command(rm, 0, Point(0, 0, 0), Point(1, 1, 1), Point(x, y, z));

        facade->run(scale_command);
        update_scene();
    } catch (const CameraError &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной камеры.");
        return;
    } catch (const ModelError &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Не загружено ни одной модели");
        return;
    }
}

void MainWindow::on_load_button_clicked()
{
    try
    {
        std::string filename = "C:\\msys64\\home\\Yokud\\4_sem_SE\\OOP\\Lab_03\\data\\mymodel.txt";

        std::shared_ptr<LoadManager> lm(new LoadManager());

        LoadCommand load_command(lm, loader, filename);

        facade->run(load_command);
    } catch (const CameraError &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Прежде чем добавлять модель, добавьте хотя бы одну камеру.");
        return;
    } catch (const FileError &error)
    {
        QMessageBox::critical(NULL, "Ошибка", "Что-то не так пошло при загрузке файла...");
        return;
    }

    update_scene();
}

void MainWindow::update_scene()
{
    drawer->clearScene();

    std::shared_ptr<DrawManager> dm(new DrawManager());
    std::shared_ptr<Object> object = facade->getScene()->getObjects()->getObjects().at(0);

    DrawCommand draw_command(dm, drawer, object);
    facade->run(draw_command);
}

void MainWindow::on_add_camera_clicked()
{
    std::shared_ptr<Camera> camera(new Camera());
    AddCommand camera_command(camera);
    facade->run(camera_command);
}
