#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h> 
#include <wait.h>

#include "read_write.h"

#define PERMISSIONS S_IRWXU | S_IRWXG | S_IRWXO
#define SHMAT_ERR_RET (void *)-1

#define READERS_CNT 5
#define WRITERS_CNT 3
#define SEM_CNT 4

#define OK 0
#define SHMGET_ERROR 1
#define SHMAT_ERROR 2
#define SEMGET_ERROR 3
#define FORK_ERROR 4
#define WAIT_ERROR 5
#define SHUTDOWN_ERROR 6

int main() 
{
    setbuf(stdout, NULL);

    int fd = shmget(IPC_PRIVATE, sizeof(int), PERMISSIONS | IPC_CREAT);
    if (fd == -1)
    {
        perror("shmget error.\n");
        return SHMGET_ERROR;
    }

    int *shared_mem_ptr = shmat(fd, 0, 0);
    if (shared_mem_ptr == SHMAT_ERR_RET) 
    {
        perror("shmat error.\n");
        return SHMAT_ERROR;
    }

    int sid = semget(IPC_PRIVATE, SEM_CNT, PERMISSIONS | IPC_CREAT);
    if (sid == -1) 
    {
        perror("semget error.\n");
        return SEMGET_ERROR;
    }

    semctl(sid, ACTIVE_WRITER, SETVAL, 0);
    semctl(sid, WRITE_QUEUE, SETVAL, 0);
    semctl(sid, ACTIVE_READER, SETVAL, 0);
    semctl(sid, READ_QUEUE, SETVAL, 0);


    for (size_t i = 0; i < WRITERS_CNT; i++) 
    {
        int child_pid = fork();

        if (child_pid == -1) 
        {
            perror("fork error(writer).\n");
            return FORK_ERROR;
        } 
        else if (child_pid == 0) 
        {
            writer_run(shared_mem_ptr, sid, i);
            return OK;
        }
    }


    for (size_t i = 0; i < READERS_CNT; i++) 
    {
        int child_pid = fork();

        if (child_pid == -1) 
        {
            perror("fork error(reader).\n");
            return FORK_ERROR;
        } 
        else if (child_pid == 0) 
        {
            reader_run(shared_mem_ptr, sid, i);
            return OK;
        }
    }

    for (size_t i = 0; i < READERS_CNT + WRITERS_CNT; i++) 
    {
        int statval;
        
        if (wait(&statval) == -1) 
        {
            perror("wait error.\n");
            return WAIT_ERROR;
        }

        if (WIFEXITED(statval) == 0)
            fprintf(stderr, "Children process %lu terminate error.\n", i);
    }

    if (shmdt((void *)shared_mem_ptr) == -1 || shmctl(fd, IPC_RMID, NULL) == -1 || semctl(sid, IPC_RMID, 0) == -1) 
    {
        perror("shutdown error.\n");
        return SHUTDOWN_ERROR;
    }

    return OK;
}