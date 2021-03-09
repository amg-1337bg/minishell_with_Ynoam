#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_command
{
    char    *cmd;
    char    **args;
    int     pipe;    // 1 if exist 0 if not
    int     cmnd_type;
}           t_cmd;

int main(int argc, char *argv[], char *env[])
{
    int i;
    if (fork() == 0)
    {
        int fd[2];
        pipe(fd);
        
        exit();
    }
    wait(&i);
}