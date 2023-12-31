#ifndef ABSLOADER_H
#define ABSLOADER_H

#include <memory>
#include "objects/object.h"
#include "loader.h"


    class AbsLoader
    {
    public:
        AbsLoader(const std::shared_ptr<BaseLoader> &loader) : loader(loader) {};
        //AbsLoader(const std::shared_ptr<AbsLoader> &loader) { this->loader = loader->loader;}
        ~AbsLoader() = default;

        virtual std::shared_ptr<Object> load() = 0;
        virtual void setLoader(std::shared_ptr<BaseLoader> loader) { this->loader = loader; };

    protected:
        std::shared_ptr<BaseLoader> loader;
    };

#endif // ABSLOADER_H
