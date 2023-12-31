#ifndef ABSGRAPHFACTORY_H
#define ABSGRAPHFACTORY_H

#include <memory>
#include "basedrawer.h"
#include "qtdrawer.h"
#include "errors/errors.h"



    class AbsGraphFactory
    {
    public:
        virtual std::unique_ptr<BaseDrawer> createGraphics() = 0;
    };

    class QtFactory : public AbsGraphFactory
    {
    public:
        QtFactory(std::shared_ptr<QGraphicsScene> &scene, std::shared_ptr<QPen> &pen, std::shared_ptr<QBrush> &brush):
            scene(scene), pen(pen), brush(brush) {};

        virtual std::unique_ptr<BaseDrawer> createGraphics() override
        {
            return std::unique_ptr<BaseDrawer>(new QtDrawer(scene, pen, brush));
        }

    protected:
        std::shared_ptr<QGraphicsScene> scene;
        std::shared_ptr<QPen> pen;
        std::shared_ptr<QBrush> brush;
    };

    class MainWindow;

    class GraphSolution
    {
    public:
        typedef std::unique_ptr<AbsGraphFactory> (MainWindow::*createGraphicsCreator)();
        using CallBackMap = std::map<std::string, createGraphicsCreator>;

        bool registration(std::string id, createGraphicsCreator createGr)
        {
            return callbacks.insert(CallBackMap::value_type(id, createGr)).second;
        }

        bool check(std::string id) { return callbacks.erase(id);}

        std::unique_ptr<AbsGraphFactory> create(MainWindow *mw, std::string id)
        {
            CallBackMap::const_iterator it = callbacks.find(id);

            if (it == callbacks.end())
                throw IdError();

            std::unique_ptr<AbsGraphFactory>cr = (mw->*(it->second))();
            return cr;
        }

    private:
        CallBackMap callbacks;
    };



#endif // ABSGRAPHFACTORY_H
