#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t mutex;

void *read_buffer(void *args)
{
    int fd2 = open("data.txt", O_RDONLY);
    char c;
    int err;

    pthread_mutex_lock(&mutex);
    while ((err = read(fd2, &c, 1)) == 1)
        write(1, &c, 1);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(void)
{
    int fd1 = open("data.txt", O_RDONLY);

    pthread_t thread;
    pthread_create(&thread, NULL, read_buffer, NULL);
    char c;
    int err;

    pthread_mutex_lock(&mutex);
    while ((err = read(fd1, &c, 1)) == 1)
        write(1, &c, 1);
    pthread_mutex_unlock(&mutex);

    pthread_join(thread, NULL);

    return 0;
}
