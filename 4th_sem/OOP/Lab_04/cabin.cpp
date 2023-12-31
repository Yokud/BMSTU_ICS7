#include "cabin.h"

Cabin::Cabin() : cur_floor(0), cur_target(-1), cur_dir(STAY), state(WAIT)
{
    cross_floor_timer.setSingleShot(true);

    QObject::connect(this, SIGNAL(cabin_achieved_target(int)), this, SLOT(stop(int)));
    QObject::connect(&doors, SIGNAL(doors_closed()), this, SLOT(wait()));
    QObject::connect(this, SIGNAL(cabin_stopped()), &doors, SLOT(start_opening()));
    QObject::connect(&cross_floor_timer, SIGNAL(timeout()), this, SLOT(move()));
    QObject::connect(this, SIGNAL(cabin_called()), this, SLOT(move()));
}

void Cabin::move()
{
    if (state != START_MOVE && state != MOVING)
        return;

    if (state == MOVING)
        cur_floor += cur_dir;
    else
        state = MOVING;

    if (cur_floor == cur_target)
        emit cabin_achieved_target(cur_floor);
    else
    {
        emit cabin_crossed_floor(cur_floor, cur_dir);
        cross_floor_timer.start(CROSSING_FLOOR);
    }
}

void Cabin::stop(int floor)
{
    if (state != MOVING)
        return;

    state = STOP;
    qDebug() << "Cabin stopped at floor №" << cur_floor + 1;
    emit cabin_stopped();
}

void Cabin::wait()
{
    if (state != STOP)
        return;

    state = WAIT;
    qDebug() << "Cabin waiting";

    emit cabin_wait(cur_floor);
}

void Cabin::cabin_get_target(int floor, const direction &dir)
{
    if (state != WAIT)
        return;

    state = START_MOVE;
    cur_target = floor;
    cur_dir = dir;

    emit cabin_called();
}
