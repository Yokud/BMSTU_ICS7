#include "facade.h"


    FacadeCreator::~FacadeCreator() {}

    std::shared_ptr<Facade> FacadeCreator::getFacade()
    {
        if (!facade)
            facade = createFacade();

        return facade;
    }

    std::shared_ptr<Facade> ConFacadeCreator::createFacade()
    {
        return std::shared_ptr<Facade>(new Facade());
    }

    void Facade::run(Command &command)
    {
        command.execute(this->scene);
    }

