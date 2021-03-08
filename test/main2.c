#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
    int i = open("file", O_WRONLY);
    int j = open("file", O_RDONLY);
    if (fork() == 0)
    {
        char *str = calloc(3, 1);
        read(j, str, 3);
        write(i, str, 3);
        exit(0);
    }
    wait(0);

    if (fork() == 0)
    {
        char *str = calloc(3, 1);
        read(j, str, 3);
        write(i, str, 3);
        exit(0);
    }
    wait(0);

}