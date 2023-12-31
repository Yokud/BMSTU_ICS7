#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define OK 0
#define FORK_ERROR 1
#define EXEC_ERROR 2

#define FORK_CNT 2
#define CMD_CNT 2


int main()
{
    int children[FORK_CNT];

    char *cmds[CMD_CNT] = {"./bubble_sort", "./avg_of_array"};
    char *args[CMD_CNT] = {NULL, NULL};

    printf("Parent process. PID: %d, Group: %d.\n\n", getpid(), getpgrp());

    for (int i = 0; i < FORK_CNT; i++)
    {
        int new_pid = fork();

        if (new_pid == -1)
        {
            perror("Can\'t fork.\n");
            return FORK_ERROR;
        }
        else if (new_pid == 0)
        {
            printf("Child process %d. PID: %d, PPID: %d, Group: %d\n", i + 1, getpid(), getppid(), getpgrp());

            int cmd_i = i % CMD_CNT;

            int rc = execlp(cmds[cmd_i], cmds[cmd_i], args[cmd_i], (char *)NULL);

            if (rc == -1)
            {
                perror("exec() failed.\n");
                return EXEC_ERROR;
            }

            return OK;
        }
        else
        {
            children[i] = new_pid;
        }
    }

    for (int i = 0; i < FORK_CNT; i++)
    {
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

    printf("Parent process. Children PID: ");

    for (int i = 0; i < FORK_CNT; i++)
        printf("%d ", children[i]);

    printf("\nParent died.\n");

    return OK;
}