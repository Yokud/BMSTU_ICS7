#ifndef POINT_H
#define POINT_H

#include <math.h>


    class Point
    {
    public:
        Point();
        Point(const double x, const double y, const double z);

        Point(const Point &point);
        Point& operator=(const Point &point);

        Point(const Point &&point);
        Point& operator=(Point &&point);

        ~Point() = default;

        Point getPos() {return *this;}
        void setPos(const Point &p) { (*this) = p;}

        void move(const double &dx, const double &dy, const double &dz);
        void scale(const double &kx, const double &ky, const double &kz);
        void rotate(const double &ox, const double &oy, const double &oz);

        double getX() const {return this->x;}
        double getY() const {return this->y;}
        double getZ() const {return this->z;}

    private:
        double x;
        double y;
        double z;

        void rotateX(const double &ox);
        void rotateY(const double &oy);
        void rotateZ(const double &oz);
    };

#endif // POINT_H
