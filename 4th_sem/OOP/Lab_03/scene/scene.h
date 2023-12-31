#ifndef SCENE_H
#define SCENE_H

#include <algorithm>
#include "objects/object.h"
#include "objects/composite.h"


class Scene
{
public:
    Scene() : objects(std::make_shared<Composite>()) {};
    ~Scene() = default;

    bool addObject(std::shared_ptr<Object> &obj);
    void removeObject(ObjIterator &obj);

    std::shared_ptr<Camera> getCamera();
    void setCamera(std::shared_ptr<Camera> &camera);

    std::shared_ptr<Composite> getObjects();

protected:
    std::shared_ptr<Composite> objects;
    std::shared_ptr<Camera> camera;
};


#endif // SCENE_H
