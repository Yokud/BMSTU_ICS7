#include "qtdrawer.h"


    QtDrawer::QtDrawer(const QtDrawer &_drawer)
    {
        this->scene = _drawer.scene;
        this->pen = _drawer.pen;
        this->brush = _drawer.brush;
    }

    void QtDrawer::clearScene()
    {
        scene->clear();
    }

    void QtDrawer::drawLine(const Point &point1, const Point &point2)
    {
        this->scene->addLine(point1.getX(), point1.getY(), point2.getX(), point2.getY(), *pen);
    }

