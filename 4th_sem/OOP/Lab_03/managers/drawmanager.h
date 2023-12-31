#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <memory>
#include "../visitor/drawvisitor.h"
#include "basemanager.h"
#include "objects/object.h"
#include "drawers/graphsfactory.h"
#include "configs/configs.h"


    class DrawManager : public BaseManager
    {
    public:
        DrawManager() = default;
        ~DrawManager() = default;

        void drawObject(std::shared_ptr<Object> &obj, std::shared_ptr<BaseDrawer> &drawer, std::shared_ptr<Camera> &camera);
    };



#endif // DRAWMANAGER_H
