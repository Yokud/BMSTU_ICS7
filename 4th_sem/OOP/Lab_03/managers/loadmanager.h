#ifndef LOADMANAGER_H
#define LOADMANAGER_H

#include <string>
#include "managers/basemanager.h"
#include "load/absloader.h"


    class LoadManager : public BaseManager
    {
    public:
        LoadManager() = default;
        ~LoadManager() = default;

        std::shared_ptr<Object> load(std::shared_ptr<AbsLoader> loader);
    };


#endif // LOADMANAGER_H
