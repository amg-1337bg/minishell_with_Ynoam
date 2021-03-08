#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_command
{
    char    *cmd;
    char    **args;
    int     pipe;    // 1 if exist 0 if not
}           t_cmd;

int main(int argc, char *argv[], char *env[])
{
    int thereIsAPipe = 0;
    int pid;
    int returnValue;
    int i = 0;
    t_cmd cmmnds[2];
    cmmnds[0].cmd = "/bin/echo";
    cmmnds[0].args = malloc(sizeof(char *)  * 4);
    cmmnds[0].args[0] = "echo";
    cmmnds[0].args[1] = "hello";
    cmmnds[0].args[2] = "world";
    cmmnds[0].args[3] = NULL;
    cmmnds[0].pipe = 1;

    cmmnds[1].cmd = "/usr/bin/grep";
    cmmnds[1].args = malloc(sizeof(char *)  * 3);
    cmmnds[1].args[0] = "grep";
    cmmnds[1].args[1] = "hello";
    cmmnds[1].args[2] = NULL;
    cmmnds[1].pipe = 0;

    while (i != 2)
    {
        int fd[2];
        if (cmmnds[i].pipe == 1)
        {
            pipe(fd);
        }
        pid = fork();
        if (pid == 0) // child process
        {
            if (cmmnds[i].pipe == 1)
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
            }
            else
            {
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]);
                close(fd[1]);
            }
            execv(cmmnds[i].cmd,cmmnds[i].args); 

        }
        waitpid(pid, &returnValue, 0);
        i++;

    }
    if (returnValue == 256)
        returnValue = 1;
    return (returnValue);
}