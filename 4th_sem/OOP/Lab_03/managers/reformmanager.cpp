#include "reformmanager.h"


    void ReformManager::reformObject(std::shared_ptr<Object> &object, const Point &move, const Point &scale, const Point &turn)
    {
        object->reform(move, scale, turn);
    }

