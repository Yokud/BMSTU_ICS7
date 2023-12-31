#include "producer.h"

struct sembuf PROD_LOCK[] = { 
    { BUFF_EMPTY, -1, 0 }, 
    { BIN_SEM, -1, 0 } 
};

struct sembuf PROD_RELEASE[] = { 
    { BIN_SEM, 1, 0 },
    { BUFF_FULL, 1, 0 }
};

int producer_run(cbuffer_t *const buf, const int sid, const int prodid, char *symb) 
{
    srand(time(NULL) + prodid);

    if (!buf)
        return BUF_ERR;

    for (size_t i = 0; i < ITER_CNT; i++) 
    {
        int sleep_time = rand() % PROD_TIME_RANGE + PROD_TIME_START;
        sleep(sleep_time);

        if (semop(sid, PROD_LOCK, SEM_SIZE) == -1)
            return PROD_LOCK_ERR;

        if (write_buffer(buf, *symb) == -1)
            return BUFF_WRITE_ERR;

        fprintf(stdout, "Producer %d write %c\n", prodid + 1, *symb);

        (*symb)++;
        if (semop(sid, PROD_RELEASE, SEM_SIZE) == -1)
            return PROD_RELEASE_ERR;
    }

    return OK;
}