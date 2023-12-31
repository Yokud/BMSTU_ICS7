#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd1 = open("data.txt", O_RDONLY);
    int fd2 = open("data.txt", O_RDONLY);
    int rc1, rc2 = 1;

    while (rc1 == 1 || rc2 == 1)
    {
        char c;
        if ((rc1 = read(fd1, &c, 1)) == 1) write(1, &c, 1);
        if ((rc2 = read(fd2, &c, 1)) == 1) write(1, &c, 1);
    }

    return 0;
}
