#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define FORK_ERROR 1
#define PIPE_ERROR 2

#define FORK_CNT 2
#define BUFF_SZ 1024
#define MSGS_CNT 2

int main(void)
{
    int children[FORK_CNT];

    int fd[2];
    char buffer[BUFF_SZ] = {0};
    char *msgs[MSGS_CNT] = {"bjldfszgkljngjsgvuwhrab", "iufwesjdnsdh"};

    if (pipe(fd) == -1)
    {
        perror("Can\'t pipe.\n");
        return PIPE_ERROR;
    }

    printf("Parent process. PID: %d, Group: %d.\n\n", getpid(), getpgrp());

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
            printf("Child process %d. PID: %d, PPID: %d, Group: %d\n", i + 1, getpid(), getppid(), getpgrp());

            int mgs_i = i % MSGS_CNT;
            close(fd[0]);
            write(fd[1], msgs[mgs_i], strlen(msgs[mgs_i]));

            printf("Child process %d. PID: %d, Message: %s\n", i + 1, getpid(), msgs[mgs_i]);

            return OK;
        }
        else
        {
            children[i] = new_pid;

            int status;
            pid_t child_pid = wait(&status);

            printf("Child process %d finished. PID: %d, Status: %d\n", i + 1, child_pid, status);

            if (WIFEXITED(status))
                printf("Child process %d finished with code: %d\n\n", i + 1, WEXITSTATUS(status));
            else if (WIFSIGNALED(status))
                printf("Child process %d finished from signal with code: %d\n\n", i + 1, WTERMSIG(status));
            else if (WIFSTOPPED(status))
                printf("Child process %d stoped by signal with code: %d\n\n", i + 1, WSTOPSIG(status));
        }
    }

    printf("Parent process. Children PID: ");

    for (int i = 0; i < FORK_CNT; i++)
        printf("%d ", children[i]);

    close(fd[1]);
    read(fd[0], buffer, BUFF_SZ);

    printf("\nParent message: %s", buffer);

    printf("\nParent died.\n");

    return OK;
}