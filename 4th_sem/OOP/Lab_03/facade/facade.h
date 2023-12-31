#ifndef FACADE_H
#define FACADE_H

#include <memory>
#include "commands/command.h"


    class Facade
    {
    public:
        Facade() : scene(std::make_shared<Scene>()) {};
        ~Facade() = default;

        void run(Command &command);

        std::shared_ptr<Scene> getScene() { return scene;};

    private:
        std::shared_ptr<Scene> scene;
    };

    class FacadeCreator
    {
    public:
        virtual ~FacadeCreator() = 0;
        std::shared_ptr<Facade> getFacade();

    protected:
        virtual std::shared_ptr<Facade> createFacade() = 0;

    private:
        std::shared_ptr<Facade> facade;
    };

    class ConFacadeCreator: public FacadeCreator
    {
    protected:
        virtual std::shared_ptr<Facade> createFacade() override;
    };


#endif // FACADE_H
