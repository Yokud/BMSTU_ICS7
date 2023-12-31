#include "model.h"


    Model::Model(const Model &_model)
    {
        this->details = _model.getDetails();
    }

    std::unique_ptr<Model> Model::clone()
    {
        return std::unique_ptr<Model>(new Model(*this));
    }

    void Model::addPoint(const Point &point)
    {
        this->details->addPoint(point);
    }

    void Model::addEdge(const Edge &edge)
    {
        this->details->addEdge(edge);
    }

    void Model::reform(const Point &move_coeff, const Point &scale_coeff, const Point &turn_coeff)
    {
        this->details->reform(move_coeff, scale_coeff, turn_coeff);
    }

    void Model::accept(std::shared_ptr<Visitor> visitor)
    {
        visitor->visit(*this);
    }

