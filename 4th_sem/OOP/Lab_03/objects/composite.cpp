#include "composite.h"


    Composite::Composite(std::shared_ptr<Object> &component)
    {
        this->objects.push_back(component);
    }

    Composite::Composite(std::vector<std::shared_ptr<Object>> vector)
    {
        this->objects = vector;
    }

    bool Composite::add(std::shared_ptr<Object> component)
    {
        this->objects.push_back(component);

        return true;
    }

    bool Composite::remove(ObjIterator &iterator)
    {
        this->objects.erase(iterator);
        return true;
    }

    ObjIterator Composite::begin()
    {
        return this->objects.begin();
    }

    ObjIterator Composite::end()
    {
        return this->objects.end();
    }

    bool Composite::isComposite() const
    {
        return true;
    }

    size_t Composite::size() const
    {
        return this->objects.size();
    }

    void Composite::reform(const Point &move, const Point &scale, const Point &turn)
    {
        for (auto elem: objects)
        {
            elem->reform(move, scale, turn);
        }
    }

    void Composite::accept(std::shared_ptr<Visitor> visitor)
    {
        visitor->visit(*this);
    }

