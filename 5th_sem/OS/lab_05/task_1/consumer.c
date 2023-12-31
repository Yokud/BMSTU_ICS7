#include "consumer.h"


struct sembuf CONS_LOCK[] = { 
    { BUFF_FULL, -1, 0 }, 
    { BIN_SEM, -1, 0 } 
};

struct sembuf CONS_RELEASE[] = { 
    { BIN_SEM, 1, 0 } ,
    { BUFF_EMPTY, 1, 0 }
};

int consumer_run(cbuffer_t *const buf, const int sid, const int consid) 
{
    srand(time(NULL) + consid);

    if (!buf)
        return BUF_ERR;

    for (int i = 0; i < ITER_CNT; i++) 
    {
        int sleep_time = rand() % CONS_TIME_RANGE + CONS_TIME_START;
        sleep(sleep_time);

        if (semop(sid, CONS_LOCK, SEM_SIZE) == -1)
            return CONS_LOCK_ERR;

        char symb;

        if (read_buffer(buf, &symb) == -1)
            return BUFF_READ_ERR;

        fprintf(stdout, "Consumer %d read %c\n", consid + 1, symb);

        if (semop(sid, CONS_RELEASE, SEM_SIZE) == -1)
            return CONS_RELEASE_ERR;
    }

    return OK;
}