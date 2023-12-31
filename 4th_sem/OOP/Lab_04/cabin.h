#ifndef CABIN_H
#define CABIN_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include "consts.h"
#include "door.h"

typedef enum {
    MOVING,
    WAIT,
    START_MOVE,
    STOP
} cabin_state;

class Cabin: public QObject
{
    Q_OBJECT

  public:
    explicit Cabin();

signals:
    void cabin_called();
    void cabin_stopped();
    void cabin_achieved_target(int);
    void cabin_crossed_floor(int, const direction &_direction);
    void cabin_wait(int floor);

public slots:
    void move();
    void stop(int floor);
    void wait();
    void cabin_get_target(int floor, const direction &dir);

private:
    int cur_floor;
    int cur_target;
    direction cur_dir;
    Doors doors;
    cabin_state state;
    QTimer cross_floor_timer;
};

#endif // CABIN_H
