#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <vector>
#include "visitor/visitor.h"
#include "point.h"

#include <string>

#define MODEL 1
#define CAMERA 2
#define COMPOSITE 3

    class Object;
    using ObjIterator = std::vector<std::shared_ptr<Object>>::iterator;

    class Object
    {
    public:
        Object() = default;
        virtual ~Object() = default;

        virtual bool add(std::shared_ptr<Object>) { return false; };
        virtual bool remove(ObjIterator &) { return false; };

        virtual ObjIterator begin() = 0;
        virtual ObjIterator end() = 0;

        virtual bool isComposite() const { return false; };
        virtual void accept(std::shared_ptr<Visitor> visitor) = 0;
        virtual void reform(const Point &move, const Point &scale, const Point &turn) = 0;

        virtual size_t info() = 0;
    };


    class VisibleObject : public Object
    {
    public:
        VisibleObject() = default;
        ~VisibleObject() = default;

        virtual bool isVisible() { return true; }

    };

    class InvisibleObject : public Object
    {
    public:
        InvisibleObject() = default;
        ~InvisibleObject() = default;

        virtual bool isVisible() { return false; }

    };


#endif // OBJECT_H
