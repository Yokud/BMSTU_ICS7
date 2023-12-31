#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 20

void *read_buffer(void *args)
{
    int fd = *(int*)args;
    FILE *fs2 = fdopen(fd, "r");

    char buff2[BUF_SIZE];
    setvbuf(fs2, buff2, _IOFBF, BUF_SIZE);

    int flag = 1;
    char c;

    while ((flag = fscanf(fs2,"%c" , &c)) == 1)
        fprintf(stdout, "thread 2: %c\n", c);

    return NULL;
}

int main(void)
{
    setbuf(stdout, NULL);

    pthread_t thread;
    int fd = open("data.txt", O_RDONLY);

    FILE *fs1 = fdopen(fd, "r");
    char buff1[BUF_SIZE];
    setvbuf(fs1, buff1, _IOFBF, BUF_SIZE);

    pthread_create(&thread, NULL, read_buffer, (void *)&fd);
    usleep(1);

    char c;
    int flag;

    while ((flag = fscanf(fs1, "%c", &c)) == 1)
        fprintf(stdout, "thread 1: %c\n", c);

    pthread_join(thread, NULL);

    return 0;
}
