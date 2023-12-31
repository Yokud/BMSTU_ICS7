#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/sem.h> 
#include <unistd.h>
#include <wait.h>

#include "buffer.h"
#include "consumer.h"
#include "producer.h"

#define PROD_CNT 3
#define CONS_CNT 3

#define PERMISSIONS S_IRWXU | S_IRWXG | S_IRWXO
#define SHMAT_ERR_RET (void *)-1

#define SEM_CNT 3
#define BIN_SEM 0
#define BUFF_FULL 1
#define BUFF_EMPTY 2

#define FREE 1

#define SHMGET_ERR -9
#define SHMAT_ERR -10
#define FORK_ERR -11
#define WAIT_ERR -12
#define SHUTDOWN_ERR -13
#define SEMGET_ERR -14

int main() 
{
    setbuf(stdout, NULL);

    int fd = shmget(IPC_PRIVATE, sizeof(cbuffer_t), PERMISSIONS | IPC_CREAT);
    if (fd == -1) 
    {
        perror("shmget error.\n");
        return SHMGET_ERR;
    }

    cbuffer_t *buffer = shmat(fd, 0, 0);
    if (buffer == SHMAT_ERR_RET) 
    {
        perror("shmat error.\n");
        return SHMAT_ERR;
    }

    if (buffer == NULL)
        return BUF_ERR;

    int fd_symb = shmget(IPC_PRIVATE, sizeof(char), PERMISSIONS | IPC_CREAT);
    if (fd_symb == -1)
    {
        perror("shmget error.\n");
        return SHMGET_ERR;
    }

    char *symb = shmat(fd_symb, 0, 0);
    if (symb == SHMAT_ERR_RET) 
    {
        perror("shmat error.\n");
        return SHMAT_ERR;
    }

    *symb = 'a';

    int sid = semget(IPC_PRIVATE, SEM_CNT, PERMISSIONS | IPC_CREAT);
    if (sid == -1) 
    {
        perror("semget error.\n");
        return SEMGET_ERR;
    }

    semctl(sid, BIN_SEM, SETVAL, FREE);
    semctl(sid, BUFF_EMPTY, SETVAL, N);
    semctl(sid, BUFF_FULL, SETVAL, 0);

    for (size_t i = 0; i < PROD_CNT; i++) 
    {
        int child_pid = fork();

        if (child_pid == -1) 
        {
            perror("fork error(producer).\n");
            return FORK_ERR;
        } 
        else if (child_pid == 0) 
        {
            producer_run(buffer, sid, i, symb);
            return OK;
        }
    }

    for (size_t i = 0; i < CONS_CNT; i++) 
    {
        int child_pid = fork();

        if (child_pid == -1) 
        {
            perror("fork error(consumer)\n.");
            return FORK_ERR;
        } 
        else if (child_pid == 0) 
        {
            consumer_run(buffer, sid, i);
            return OK;
        }
    }

    for (size_t i = 0; i < PROD_CNT + CONS_CNT; i++) 
	{
        int statval;
        
        if (wait(&statval) == -1) 
        {
            perror("wait error.\n");
            return WAIT_ERR;
        }

        if (WIFEXITED(statval) == 0)
            fprintf(stderr, "Child process %lu terminate error.\n", i);
    }

    if (shmdt((void *)buffer) == -1 || shmctl(fd, IPC_RMID, NULL) == -1 || semctl(sid, IPC_RMID, 0) == -1 || shmdt((void *)symb) == -1 || shmctl(fd_symb, IPC_RMID, NULL) == -1) 
    {
        perror("Shutdown error.\n");
        return SHUTDOWN_ERR;
    }


    return OK;
}