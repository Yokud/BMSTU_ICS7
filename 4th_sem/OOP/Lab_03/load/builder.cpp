#include "builder.h"


    bool ModelBuilder::isBuild() const
    {
        return this->model_ptr != nullptr;
    }

    void ModelBuilder::buildPtr()
    {
        this->model_ptr = std::make_shared<Model>();
    }

    void ModelBuilder::buildPoint(const double &x, const double &y, const double &z)
    {
        if (!isBuild())
        {
            std::string s = "Model pointer doesn't exist";
            throw ModelError(s);
        }

        Point pt_obj(x, y, z);
        this->model_ptr->addPoint(pt_obj);
    }

    void ModelBuilder::buildEdge(const size_t &pt1, const size_t &pt2)
    {
        if (!isBuild())
        {
            std::string s = "Model pointer doesn't exist";
            throw ModelError(s);
        }

        Edge link_obj(pt1, pt2);
        this->model_ptr->addEdge(link_obj);
    }

    std::shared_ptr<Model> ModelBuilder::get()
    {
        return model_ptr;
    }

