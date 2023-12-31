#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *write_buffer(void *args)
{
    FILE *f = fopen("out.txt", "w");

    for (char c = 'b'; c <= 'z'; c += 2)
        fprintf(f, "%c", c);

    fclose(f);
    return NULL;
}

int main()
{
    FILE *f1 = fopen("out.txt", "w");

    pthread_t thread;
    int rc = pthread_create(&thread, NULL, write_buffer, NULL);

    for (char c = 'a'; c <= 'z'; c += 2)
        fprintf(f1, "%c", c);

    pthread_join(thread, NULL);
    fclose(f1);

    return 0;
}
