#include "drawmanager.h"

    void DrawManager::drawObject(std::shared_ptr<Object> &obj, std::shared_ptr<BaseDrawer> &drawer, std::shared_ptr<Camera> &camera)
    {
        std::shared_ptr<Visitor> visitor(new DrawVisitor(drawer, camera));

        obj->accept(visitor);
    }

