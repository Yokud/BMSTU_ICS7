#include <stdio.h>
#include <unistd.h>


#define OK 0
#define FORK_ERROR 1

#define FORK_CNT 2
#define SLP_SCND 3


int main()
{
    int children[FORK_CNT];

    printf("Parent process. PID: %d, Group: %d\n", getpid(), getpgrp());

    for (int i = 0; i < FORK_CNT; i++)
    {
        int new_pid = fork();

        if (new_pid == -1)
        {
            perror("Can\'t fork.");
            return FORK_ERROR;
        }
        else if (new_pid == 0)
        {
            sleep(SLP_SCND);
            printf("Child process %d. PID: %d, PPID: %d, Group: %d\n", i + 1, getpid(), getppid(), getpgrp());
            return OK;
        }
        else
        {
            children[i] = new_pid;
        }
    }

    printf("Parent process. Children PID: ");

    for (int i = 0; i < FORK_CNT; i++)
        printf("%d ", children[i]);

    printf("\nParent died.\n");

    return OK;
}