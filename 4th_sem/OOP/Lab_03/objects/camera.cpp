#include "camera.h"


    void Camera::reform(const Point &mov_val, const Point &scale_val, const Point &rot_val)
    {
        this->current_pos.move(mov_val.getX(), mov_val.getY(), mov_val.getZ());

        this->current_pos.scale(scale_val.getX(), scale_val.getY(), scale_val.getZ());

        this->current_pos.rotate(rot_val.getX(), rot_val.getY(), rot_val.getZ());
    }

    void Camera::accept(std::shared_ptr<Visitor> visitor)
    {
        visitor->visit(*this);
    }

