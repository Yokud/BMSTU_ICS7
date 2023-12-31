#ifndef SERVICE_UNIT_H
#define SERVICE_UNIT_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "a_queue.h"
#include "l_queue.h"

#define EPS 1e-6

typedef struct
{
    double ENTRY_TIME_T1_MIN;
    double ENTRY_TIME_T1_MAX;
    double ENTRY_TIME_T2_MIN;
    double ENTRY_TIME_T2_MAX;

    double PROC_TIME_T1_MIN;
    double PROC_TIME_T1_MAX;
    double PROC_TIME_T2_MIN;
    double PROC_TIME_T2_MAX;
} preset_t;

typedef enum {FIRST, SECOND, NONE} req_type;

typedef struct 
{
    double full_work_time;
    double wait_time;

    size_t in_t1, out_t1;
    size_t in_t2, out_t2;
    size_t dumped;

    double person_time_t1, person_time_t2;

} stats_t;

typedef int (*push_fp)(void *, void *);
typedef int (*pop_fp)(void *, void *);
typedef bool (*empt_fp)(void *);
typedef bool (*full_fp)(void *);

int unit_sim(void *q1, void *q2, push_fp push, pop_fp pop, empt_fp is_empty, full_fp is_full, size_t count, size_t step, bool verbose, preset_t t, stats_t *stats);

#endif
