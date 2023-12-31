#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <vector>
#include "object.h"


    class Composite : public Object
    {
    public:
        Composite() = default;
        Composite(std::shared_ptr<Object> &component);
        Composite(std::vector<std::shared_ptr<Object>> vector);

        size_t size() const;

        virtual bool add(std::shared_ptr<Object> component) override;
        virtual bool remove(ObjIterator &iterator) override;

        virtual ObjIterator begin() override;
        virtual ObjIterator end() override;

        virtual bool isComposite() const override;
        virtual void reform(const Point &move, const Point &scale, const Point &turn) override;
        virtual void accept(std::shared_ptr<Visitor> visitor) override;

        std::vector<std::shared_ptr<Object>> getObjects() { return objects; };

        virtual size_t info() override { return COMPOSITE;};

    private:
        std::vector<std::shared_ptr<Object>> objects;

    };

#endif // COMPOSITE_H
