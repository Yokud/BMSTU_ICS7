#ifndef MODEL_H
#define MODEL_H

#include "objects/object.h"
#include "edge.h"
#include "modeldetails.h"
#include "visitor/visitor.h"


    class Model : public VisibleObject
    {
    public:
        Model() : details(new ModelDetails) {};
        Model(const std::shared_ptr<ModelDetails> details) : details(details) {};
        Model(const Model &model);
        ~Model() = default;

        std::unique_ptr<Model> clone();

        const std::shared_ptr<ModelDetails> getDetails() const { return details; };
        void addPoint(const Point &point);
        void addEdge(const Edge &link);

        virtual ObjIterator begin() override { return ObjIterator();};
        virtual ObjIterator end() override { return ObjIterator();};

        virtual void reform(const Point &move, const Point &scale, const Point &turn) override;
        virtual void accept(std::shared_ptr<Visitor> visitor) override;

        virtual size_t info() override { return MODEL;};

    private:
        std::shared_ptr<ModelDetails> details;
    };


#endif // MODEL_H
