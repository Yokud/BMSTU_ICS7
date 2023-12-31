#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include "consts.h"

typedef enum
{
    BUSY,
    FREE
} controller_state;

class ControlPanel: public QObject
{
    Q_OBJECT
public:
    explicit ControlPanel(): state(FREE), cur_floor(0), cur_target(-1), cur_dir(STAY), is_target(FLOORS_COUNT, false)
    {
        QObject::connect(this, SIGNAL(panel_new_target(int,direction)), this, SLOT(busy(int,direction)));
    }

    void new_target(int floor);

public slots:
    void busy(int floor, const direction &_direction);
    void free(int floor);

signals:
    void panel_new_target(int floor, const direction &_direction);

private:
    void nextTarget();
    controller_state state;
    int cur_floor;
    int cur_target;
    direction cur_dir;
    QVector<bool> is_target;
};

#endif // CONTROLPANEL_H
