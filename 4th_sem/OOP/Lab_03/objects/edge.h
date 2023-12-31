#ifndef EDGE_H
#define EDGE_H

#include <stdlib.h>


    class Edge
    {
    public:
        Edge() : pt1_index(0), pt2_index(0) {};
        Edge(const size_t &pt1, const size_t &pt2) : pt1_index(pt1), pt2_index(pt2) {};
        Edge(const Edge &edge);
        ~Edge() = default;

        size_t getFst() const;
        size_t getSnd() const;

        void setFst(const size_t &fst);
        void setSnd(const size_t &snd);

    private:
        size_t pt1_index;
        size_t pt2_index;
    };


#endif // EDGE_H
