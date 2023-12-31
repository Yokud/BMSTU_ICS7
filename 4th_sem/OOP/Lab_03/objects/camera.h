#ifndef CAMERA_H
#define CAMERA_H

#include "object.h"


    class Camera: public InvisibleObject
    {
    public:
        Camera() = default;
        Camera(const Point &pos) : current_pos(pos) {};
        Camera(std::shared_ptr<Camera> &cam) : current_pos(cam->getPos()) {}
        ~Camera() = default;

        virtual bool add(std::shared_ptr<Object>) override { return false; };
        virtual bool remove(ObjIterator &) override { return false; };
        virtual ObjIterator begin() override { return ObjIterator();};
        virtual ObjIterator end() override { return ObjIterator();};

        virtual bool isComposite() const override { return false; };
        virtual void reform(const Point &pos, const Point &turn, const Point &scale) override;
        virtual void accept(std::shared_ptr<Visitor> visitor) override;
        Point getPos() { return current_pos; };

        virtual size_t info() override { return CAMERA;};
    private:
        Point current_pos;
    };



#endif // CAMERA_H
