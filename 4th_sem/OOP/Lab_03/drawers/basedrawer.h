#ifndef BASEDRAWER_H
#define BASEDRAWER_H


class Point;


    class BaseDrawer
    {
    public:
        BaseDrawer() = default;
        virtual ~BaseDrawer() = default;
        virtual void drawLine(const Point &point1, const Point &point2) = 0;
        virtual void clearScene() = 0;
    };


#endif // BASEDRAWER_H
