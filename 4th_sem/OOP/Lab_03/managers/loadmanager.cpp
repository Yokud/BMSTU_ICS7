#include "loadmanager.h"


    std::shared_ptr<Object> LoadManager::load(std::shared_ptr<AbsLoader> loader)
    {
        return loader->load();
    }


