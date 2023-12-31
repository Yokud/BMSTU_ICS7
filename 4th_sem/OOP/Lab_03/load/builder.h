#ifndef BUILDER_H
#define BUILDER_H

#include <string>
#include "../objects/model.h"
#include "errors/errors.h"


    class BaseBuilder
    {
    public:
        BaseBuilder() = default;
        ~BaseBuilder() = default;

        virtual bool isBuild() const = 0;
        virtual void buildPtr() = 0;
        virtual void buildPoint(const double &x, const double &y, const double &z) = 0;
        virtual void buildEdge(const size_t &pt1, const size_t &pt2) = 0;

        virtual std::shared_ptr<Model> get() = 0;
    };

    class ModelBuilder : public BaseBuilder
    {
    public:
        ModelBuilder() : model_ptr(nullptr) {};
        ~ModelBuilder() = default;

        virtual bool isBuild() const override;
        virtual void buildPtr() override;
        virtual void buildPoint(const double &x, const double &y, const double &z) override;
        virtual void buildEdge(const size_t &pt1, const size_t &pt2) override;

        virtual std::shared_ptr<Model> get() override;

    private:
        std::shared_ptr<Model> model_ptr;
    };


#endif // BUILDER_H
