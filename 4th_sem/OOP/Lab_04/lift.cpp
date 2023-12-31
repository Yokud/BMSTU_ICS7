#include "lift.h"

Lift::Lift()
{
    QObject::connect(&controller, SIGNAL(panel_new_target(int,direction)), &cabin, SLOT(cabin_get_target(int,direction)));
    QObject::connect(&cabin, SIGNAL(cabin_crossed_floor(int,direction)), &controller, SLOT(busy(int,direction)));
    QObject::connect(&cabin, SIGNAL(cabin_wait(int)), &controller, SLOT(free(int)));
}

void Lift::call(int floor) { controller.new_target(floor); }
