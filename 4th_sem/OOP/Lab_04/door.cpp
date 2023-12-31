#include "door.h"

Doors::Doors() : cur_state(CLOSED)
{
    doors_stay_timer.setInterval(WAITING_TIME);

    doors_stay_timer.setSingleShot(true);
    doors_open_timer.setSingleShot(true);
    doors_close_timer.setSingleShot(true);

    QObject::connect(&doors_open_timer, SIGNAL(timeout()), this, SLOT(opened()));
    QObject::connect(&doors_close_timer, SIGNAL(timeout()), this, SLOT(closed()));
    QObject::connect(this, SIGNAL(doors_opened()), &doors_stay_timer, SLOT(start()));
    QObject::connect(&doors_stay_timer, SIGNAL(timeout()), this, SLOT(start_closing()));
}

void Doors::start_opening()
{
    if (cur_state != CLOSING && cur_state != CLOSED)
        return;

    qDebug() << "Doors are opening...";
    if (cur_state == CLOSED)
    {
        cur_state = OPENING;
        doors_open_timer.start(DOORS_TIME);
    }
    else
    {
        cur_state = OPENING;
        int t = doors_close_timer.remainingTime();
        doors_close_timer.stop();
        doors_open_timer.start(DOORS_TIME - t);
    }
}

void Doors::start_closing()
{
    if (cur_state != OPENED)
        return;

    cur_state = CLOSING;

    qDebug() << "Doors are closing...";

    doors_close_timer.start(DOORS_TIME);
}

void Doors::opened()
{
    if (cur_state != OPENING)
        return;

    cur_state = OPENED;
    qDebug() << "The doors are opened.";

    emit doors_opened();
}

void Doors::closed()
{
    if (cur_state != CLOSING)
        return;

    cur_state = CLOSED;
    qDebug() << "The doors are closed.";

    emit doors_closed();
}
