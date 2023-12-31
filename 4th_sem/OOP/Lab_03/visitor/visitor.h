#ifndef VISITOR_H
#define VISITOR_H


#include <memory>

    class Camera;
    class Model;
    class Composite;

    class Visitor
    {
    public:
        Visitor() = default;

        virtual void visit(Camera &cam) = 0;
        virtual void visit(Model &model) = 0;
        virtual void visit(Composite &composite) = 0;
    };


#endif // VISITOR_H
