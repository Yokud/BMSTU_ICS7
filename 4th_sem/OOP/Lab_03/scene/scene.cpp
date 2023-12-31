#include "scene.h"


bool Scene::addObject(std::shared_ptr<Object> &obj)
{
    return this->objects->add(obj);
}

void Scene::removeObject(ObjIterator &it)
{
    if (it < this->objects->end())
        objects->remove(it);
}

std::shared_ptr<Composite> Scene::getObjects()
{
    return this->objects;
}

std::shared_ptr<Camera> Scene::getCamera()
{
    return this->camera;
}

void Scene::setCamera(std::shared_ptr<Camera> &camera)
{
    this->camera = camera;
}
