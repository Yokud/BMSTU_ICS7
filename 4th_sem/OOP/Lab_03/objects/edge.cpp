#include "edge.h"


    Edge::Edge(const Edge &edge)
    {
        this->pt1_index = edge.pt1_index;
        this->pt2_index = edge.pt2_index;
    }

    size_t Edge::getFst() const
    {
        return this->pt1_index;
    }

    size_t Edge::getSnd() const
    {
        return this->pt2_index;
    }

    void Edge::setFst(const size_t &fst)
    {
        this->pt1_index = fst;
    }

    void Edge::setSnd(const size_t &snd)
    {
        this->pt2_index = snd;
    }

