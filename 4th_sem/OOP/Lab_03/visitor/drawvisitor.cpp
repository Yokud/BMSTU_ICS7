#include "drawvisitor.h"


void DrawVisitor::visit(Camera &cam) {}

    void DrawVisitor::visit(Model &model)
    {
        auto points = model.getDetails()->getPoints();

        for (auto edge: model.getDetails()->getEdges())
        {

            this->drawer->drawLine(
                        projectPoint(points.at(edge.getFst())),
                        projectPoint(points.at(edge.getSnd()))
            );
        }
    }

    void DrawVisitor::visit(Composite &composite)
    {
        composite.accept(std::make_shared<DrawVisitor>(*this));
    }

    void DrawVisitor::setDrawer(std::shared_ptr<BaseDrawer> &drawer)
    {
        this->drawer = drawer;
    }

    void DrawVisitor::setCamera(std::shared_ptr<Camera> &camera)
    {
        this->cam = camera;
    }

    Point DrawVisitor::projectPoint(const Point &_point)
    {
        return Point(_point.getX() + cam->getPos().getX(), _point.getY() + cam->getPos().getX(), _point.getZ());
    }

