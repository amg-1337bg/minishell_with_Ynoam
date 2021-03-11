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
    int fd[2];
    int pid;
    pipe(fd);
    pid = fork();
    if (pid == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        char *args[]= {"cat", "/dev/random", NULL};
        execve("/bin/cat", args, NULL);
    }
    pid = fork();
    if (pid == 0)
    {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        char *args[]= {"head", NULL};
        execve("/usr/bin/head", args, NULL);
    }
    int result;
    waitpid(pid, &result, 0);
    close(fd[0]);
    close(fd[1]);
    while(1);
}