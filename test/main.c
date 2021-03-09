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
    int pid;
    int returnvalue;
    pid = fork();
    if (pid == 0)
    {
        int fd[2];
        pipe(fd);
        pid = fork();
        if (pid == 0)
        {

        }
        exit(0);
    }
    waitpid(pid, &returnvalue, 0);
    return (returnvalue);
}