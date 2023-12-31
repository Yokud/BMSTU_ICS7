#ifndef __PRODUCER_H__
#define __PRODUCER_H__

#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "buffer.h"

#define BIN_SEM 0
#define BUFF_FULL 1
#define BUFF_EMPTY 2

#define ITER_CNT 8
#define SEM_SIZE 2

#define PROD_TIME_START 1
#define PROD_TIME_RANGE 9

#define BUFF_WRITE_ERR -6
#define PROD_LOCK_ERR -7
#define PROD_RELEASE_ERR -8

int producer_run(cbuffer_t *const buffer, const int sid, const int prodid, char *symb);

#endif