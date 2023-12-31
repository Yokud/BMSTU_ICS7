#ifndef QTDRAWER_H
#define QTDRAWER_H

#include <QGraphicsScene>
#include "basedrawer.h"
#include "objects/point.h"

class QtDrawer : public BaseDrawer
{
public:
    QtDrawer() : scene(nullptr), pen(nullptr), brush(nullptr) {};
    QtDrawer(std::shared_ptr<QGraphicsScene> &scene, std::shared_ptr<QPen> &pen, std::shared_ptr<QBrush> &brush):
        scene(scene), pen(pen), brush(brush) {};
    QtDrawer(const QtDrawer &_drawer);

    virtual void drawLine(const Point &point1, const Point &point2) override;
    virtual void clearScene() override;

private:
    std::shared_ptr<QGraphicsScene> scene;
    std::shared_ptr<QPen> pen;
    std::shared_ptr<QBrush> brush;
};

#endif // QTDRAWER_H
