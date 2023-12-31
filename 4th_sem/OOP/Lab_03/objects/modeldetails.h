#ifndef MODELDETAILS_H
#define MODELDETAILS_H

#include <vector>
#include "point.h"
#include "edge.h"


    class ModelDetails
    {
    public:
        ModelDetails() = default;
        ModelDetails(std::vector<Point> &points, std::vector<Edge> &edges) : points(points), edges(edges) {};
        ~ModelDetails() = default;

        void addPoint(const Point &pt);
        void addEdge(const Edge &edge);
        const std::vector<Point> &getPoints() const;
        const std::vector<Edge> &getEdges() const;

        void reform(const Point &move_val, const Point &scale_val, const Point &turn_val);

    private:
        std::vector<Point> points;
        std::vector<Edge> edges;
    };


#endif // MODELDETAILS_H
