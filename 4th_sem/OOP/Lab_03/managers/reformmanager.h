#ifndef REFORMMANAGER_H
#define REFORMMANAGER_H

#include <memory>
#include "basemanager.h"
#include "objects/object.h"


    class ReformManager : public BaseManager
    {
    public:
        ReformManager() = default;
        ~ReformManager() = default;

        void reformObject(std::shared_ptr<Object> &object, const Point &move, const Point &scale, const Point &turn);
    };



#endif // REFORMMANAGER_H
