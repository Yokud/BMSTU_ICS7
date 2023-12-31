#include "point.h"


    Point::Point()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    Point::Point(const double x, const double y, const double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Point::Point(const Point &point)
    {
        this->x = point.x;
        this->y = point.y;
        this->z = point.z;
    }

    Point& Point::operator=(const Point& point)
    {
        this->x = point.x;
        this->y = point.y;
        this->z = point.z;

        return *this;
    }

    Point::Point(const Point &&point)
    {
        this->x = point.x;
        this->y = point.y;
        this->z = point.z;
        point.~Point();
    }

    Point& Point::operator=(Point &&point)
    {
        this->x = point.x;
        this->y = point.y;
        this->z = point.z;
        point.~Point();

        return *this;
    }

    void Point::move(const double &dx, const double &dy, const double &dz)
    {
        this->x += dx;
        this->y += dy;
        this->z += dz;
    }

    void Point::scale(const double &kx, const double &ky, const double &kz)
    {
        this->x *= kx;
        this->y *= ky;
        this->z *= kz;
    }

    void Point::rotate(const double &ox, const double &oy, const double &oz)
    {
        this->rotateX(ox);
        this->rotateY(oy);
        this->rotateZ(oz);
    }

    void Point::rotateX(const double &ox)
    {
        const double temp_y = this->y;
        const double temp_z = this->z;
        this->y = temp_y * cos(ox * M_PI / 180.0) - temp_z * sin(ox * M_PI / 180.0);
        this->z = temp_y * sin(ox * M_PI / 180.0) + temp_z * cos(ox * M_PI / 180.0);
    }

    void Point::rotateY(const double &oy)
    {
        const double temp_x = this->x;
        const double temp_z = this->z;
        this->x = temp_x * cos(oy * M_PI / 180) - temp_z * sin(oy * M_PI / 180);
        this->z = temp_x * sin(oy * M_PI / 180) + temp_z * cos(oy * M_PI / 180);
    }

    void Point::rotateZ(const double &oz)
    {
        const double temp_x = this->x;
        const double temp_y = this->y;
        this->x = temp_x * cos(oz * M_PI / 180) - temp_y * sin(oz * M_PI / 180);
        this->y = temp_x * sin(oz * M_PI / 180) + temp_y * cos(oz * M_PI / 180);
    }


