#ifndef __READ_WRITE_H__
#define __READ_WRITE_H__

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define OK 0
#define SHRDMEM_PTR_ERR -1
#define WRITE_LOCK_ERR -2
#define WRITE_RELEASE_ERR -3
#define READ_LOCK_ERR -4
#define READ_RELEASE_ERR -5

#define ITER_CNT 8
#define TIME_RANGE 5
#define TIME_START 1

#define ACTIVE_READER 0
#define ACTIVE_WRITER 1
#define WRITE_QUEUE 2
#define READ_QUEUE 3

int reader_run(int *const shaered_mem, const int sid, const int rid);
int writer_run(int *const shaered_mem, const int sid, const int wid);

#endif