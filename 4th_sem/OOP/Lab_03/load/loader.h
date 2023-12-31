#ifndef BASELOADER_H
#define BASELOADER_H

#include <memory>
#include <string>
#include <fstream>

#include "objects/model.h"
#include "builder.h"


    class BaseLoader
    {
    public:
        BaseLoader() = default;
        virtual ~BaseLoader() = default;

        virtual std::shared_ptr<Object> load(std::shared_ptr<BaseBuilder> builder) = 0;
        virtual void open(std::string &fname) = 0;
        virtual void close() = 0;
    };

    class FileLoader : public BaseLoader
    {
    public:
        FileLoader() = default;
        virtual ~FileLoader() = default;

        virtual std::shared_ptr<Object> load(std::shared_ptr<BaseBuilder> builder) override;
        virtual void open(std::string &fname) override;
        virtual void close() override;

    protected:
        std::ifstream file;
    };


#endif // BASELOADER_H
