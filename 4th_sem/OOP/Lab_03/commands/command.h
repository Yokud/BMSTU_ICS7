#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <memory>
#include "objects/object.h"
#include "drawers/basedrawer.h"
#include "visitor/drawvisitor.h"
#include "scene/scene.h"
#include "load/modelloader.h"

#include "managers/drawmanager.h"
#include "managers/loadmanager.h"
#include "managers/reformmanager.h"

   class Command
    {
    public:
        Command() = default;
        virtual ~Command() = default;
        virtual void execute(std::shared_ptr<Scene> &scene) = 0;
    };

    class DrawCommand : public Command
    {
    public:
        DrawCommand() = delete;
        DrawCommand(std::shared_ptr<DrawManager> &man, std::shared_ptr<BaseDrawer> &drawer, std::shared_ptr<Object> &obj) :
            manager(man), drawer(drawer), obj(obj) {};
        ~DrawCommand() = default;

        virtual void execute(std::shared_ptr<Scene> &scene) override
        {
            auto cam = std::make_shared<Camera>(scene->getCamera()->getPos());
            std::shared_ptr<Visitor> draw_visitor = std::make_shared<DrawVisitor>(drawer, cam);

            manager->drawObject(obj, drawer, cam);
        }

    private:
        std::shared_ptr<DrawManager> manager;
        std::shared_ptr<BaseDrawer> drawer;
        std::shared_ptr<Object> obj;
    };

    class LoadCommand : public Command
    {
    public:
        LoadCommand() = delete;
        LoadCommand(std::shared_ptr<LoadManager> &man, std::shared_ptr<BaseLoader> &loader, const std::string &fname) :
            manager(man), loader(loader), fname(fname) {};
        ~LoadCommand() = default;

        virtual void execute(std::shared_ptr<Scene> &scene) override
        {
            loader->open(fname);

            auto new_obj = manager->load(std::make_shared<ModelLoader>(loader));

            loader->close();

            scene->addObject(new_obj);
        }

    private:
        std::shared_ptr<LoadManager> manager;
        std::shared_ptr<BaseLoader> loader;
        std::string fname;
    };

    class AddCommand : public Command
    {
    public:
        AddCommand() = delete;
        AddCommand(const std::shared_ptr<Object> &obj) : obj(obj) {};
        ~AddCommand() = default;

        virtual void execute(std::shared_ptr<Scene> &scene) override
        {
            scene->addObject(obj);
        }

    private:
        std::shared_ptr<Object> obj;
    };

    class RemoveCommand : public Command
    {
    public:
        RemoveCommand() = delete;
        RemoveCommand(std::shared_ptr<Object> &obj) : obj(obj) {};
        ~RemoveCommand() = default;

        virtual void execute(std::shared_ptr<Scene> &scene) override
        {
            auto it = find(scene->getObjects()->begin(), scene->getObjects()->end(), obj);

            scene->removeObject(it);
        }

    private:
        std::shared_ptr<Object> obj;
    };

    class ReformCommand : public Command
    {
    public:
        ReformCommand() = delete;
        ReformCommand(std::shared_ptr<ReformManager> &man, const size_t &numb, const Point &move, const Point &scale, const Point &turn) :
            manager(man), model_numb(numb), move(move), scale(scale), turn(turn) {}
        ~ReformCommand() = default;

        virtual void execute(std::shared_ptr<Scene> &scene) override
        {
            auto obj = scene->getObjects()->getObjects().at(model_numb);
            manager->reformObject(obj, move, scale, turn);
        }

    private:
        std::shared_ptr<ReformManager> manager;
        size_t model_numb;

        Point move;
        Point scale;
        Point turn;
    };

    class SetCommand : public Command
    {
    public:
        SetCommand() = delete;
        ~SetCommand() = default;

        SetCommand(std::shared_ptr<Scene> new_scene = nullptr) : new_scene(new_scene) {};
        SetCommand(std::shared_ptr<Camera> camera = nullptr) : camera(camera) {};

        virtual void execute(std::shared_ptr<Scene> &scene) override
        {
            if (new_scene)
                scene = new_scene;
            else if (camera)
                scene->setCamera(camera);
        }

    private:
        std::shared_ptr<Scene> new_scene {nullptr};
        std::shared_ptr<Camera> camera {nullptr};
    };


#endif // COMMAND_H
