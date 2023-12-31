#ifndef CONSTS_H
#define CONSTS_H

const int FLOORS_COUNT = 5;
const int WAITING_TIME = 7000;
const int DOORS_TIME = 2000;
const int CROSSING_FLOOR = 3000;

typedef enum{
    DOWN = -1,
    STAY,
    UP
} direction;

#endif // CONSTS_H
