#ifndef DRAWVISITOR_H
#define DRAWVISITOR_H


#include "visitor.h"
#include "objects/camera.h"
#include "objects/model.h"
#include "objects/composite.h"
#include "drawers/basedrawer.h"


    class DrawVisitor : public Visitor
    {
    public:
        DrawVisitor(std::shared_ptr<BaseDrawer> &drawer, std::shared_ptr<Camera> &camera) : drawer(drawer), cam(camera) {};

        virtual void visit(Camera &cam) override;
        virtual void visit(Model &model) override;
        virtual void visit(Composite &composite) override;

        void setDrawer(std::shared_ptr<BaseDrawer> &drawer);
        void setCamera(std::shared_ptr<Camera> &camera);

    private:
        std::shared_ptr<BaseDrawer> drawer;
        std::shared_ptr<Camera> cam;

        Point projectPoint(const Point &point);
    };


#endif // DRAWVISITOR_H
