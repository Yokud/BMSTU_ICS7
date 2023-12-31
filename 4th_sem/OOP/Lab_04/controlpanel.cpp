#include "controlpanel.h"

void ControlPanel::new_target(int floor)
{
    qDebug() << "Get new target: floor №" << floor + 1;
    is_target[floor] = true;

    cur_dir = (cur_floor > floor) ? DOWN : UP;

    if (state == FREE)
        nextTarget();
}

void ControlPanel::nextTarget()
{
    if (is_target[cur_floor])
    {
        is_target[cur_floor] = false;
        emit panel_new_target(cur_floor, STAY);
    }
    else
    {
        if (cur_dir == DOWN)
            for (int i = FLOORS_COUNT - 1; i > -1; i--)
            {
                if (is_target[i])
                {
                    is_target[i] = false;
                    if (i < cur_floor)
                        emit panel_new_target(i, DOWN);
                    else
                        emit panel_new_target(i, UP);
                    return;
                }
            }

        for (int i = 0; i < FLOORS_COUNT; i++)
            if (is_target[i])
            {
                is_target[i] = false;
                if (i > cur_floor)
                    emit panel_new_target(i, UP);
                else
                    emit panel_new_target(i, DOWN);
                break;
            }
    }
}

void ControlPanel::busy(int floor, const direction &_direction)
{
    if (state == FREE)
    {
        state = BUSY;
        cur_target = floor;
        cur_dir = _direction;
    }
    else if (state == BUSY)
    {
        qDebug() << "Passed floor №" << floor + 1;
        cur_floor += cur_dir;
    }
}

void ControlPanel::free(int floor)
{
    state = FREE;
    cur_floor = floor;
    nextTarget();
}
