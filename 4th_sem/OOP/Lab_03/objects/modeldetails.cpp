#include "modeldetails.h"


    void ModelDetails::addPoint(const Point &pt)
    {
        this->points.push_back(pt);
    }

    void ModelDetails::addEdge(const Edge &edge)
    {
        this->edges.push_back(edge);
    }

    const std::vector<Point> &ModelDetails::getPoints() const
    {
        return this->points;
    }

    const std::vector<Edge> &ModelDetails::getEdges() const
    {
        return this->edges;
    }

    void ModelDetails::reform(const Point &move_val, const Point &scale_val, const Point &turn_val)
    {
        for (auto &pt: points)
            {
                pt.move(move_val.getX(), move_val.getY(), move_val.getZ());
                pt.scale(scale_val.getX(), scale_val.getY(), scale_val.getZ());
                pt.rotate(turn_val.getX(), turn_val.getY(), turn_val.getZ());
            }
    }

