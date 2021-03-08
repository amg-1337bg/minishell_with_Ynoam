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
    int pid;
    int returnValue;
    int i = 0;
    t_cmd cmmnds[3];
    cmmnds[0].cmd = "/bin/echo";
    cmmnds[0].args = malloc(sizeof(char *)  * 4);
    cmmnds[0].args[0] = "echo";
    cmmnds[0].args[1] = "hello";
    cmmnds[0].args[2] = "world";
    cmmnds[0].args[3] = NULL;
    cmmnds[0].pipe = 1;

    cmmnds[1].cmd = "/usr/bin/grep";
    cmmnds[1].args = malloc(sizeof(char *)  * 4);
    cmmnds[1].args[0] = "grep";
    cmmnds[1].args[1] = "--color"; 
    cmmnds[1].args[2] = "hello";
    cmmnds[1].args[3] = NULL;
    cmmnds[1].pipe = 1;

    // cmmnds[1].cmd = "/usr/bin/vim";
    // cmmnds[1].args = malloc(sizeof(char *)  * 4);
    // cmmnds[1].args[0] = "vim";
    // cmmnds[1].args[1] = "-"; 
    // cmmnds[1].args[2] = NULL;
    // cmmnds[1].pipe = 0;

    cmmnds[2].cmd = "/bin/ls";
    cmmnds[2].args = malloc(sizeof(char *)  * 2);
    cmmnds[2].args[0] = "ls";
    cmmnds[2].args[1] = NULL;
    cmmnds[2].pipe = 0;

    int fd[2];
    while (i != 3)
    {
        if (cmmnds[i].pipe == 1)
        {
            pipe(fd);
        }
        pid = fork();
        if (pid == 0) // child process
        {
            if (cmmnds[i].pipe == 1)
            {
                dup2(fd[1], STDOUT_FILENO); // write to the pipe
                close(fd[0]);
                close(fd[1]);
            }
            else
            {
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]);
                close(fd[1]);
            }
            execve(cmmnds[i].cmd,cmmnds[i].args, env); 
        }
        if (cmmnds[i].pipe == 0)
        {
            close(fd[0]);
            close(fd[1]);
        }
        waitpid(pid, &returnValue, 0);
        i++;

    }
    if (returnValue == 256)
        returnValue = 1;
    // while(1);
    return (returnValue);
}