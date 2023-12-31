#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    FILE *f1 = fopen("out.txt", "w");
    FILE *f2 = fopen("out.txt", "w");

    for (char c = 'a'; c <= 'z'; c++)
        fprintf(c % 2 ? f1 : f2, "%c", c);

    fclose(f2);
    fclose(f1);

    return 0;
}
