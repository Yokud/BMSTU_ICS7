#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "absloader.h"
#include "loader.h"


    class ModelLoader : public AbsLoader
    {
    public:
        ModelLoader(const std::shared_ptr<BaseLoader> &loader): AbsLoader(loader) { builder = std::make_shared<ModelBuilder>();};
        ~ModelLoader() = default;

        virtual std::shared_ptr<Object> load() override { return loader->load(this->builder);};

    private:
        std::shared_ptr<BaseBuilder> builder;
    };


#endif // MODELLOADER_H
