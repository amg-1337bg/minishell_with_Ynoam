#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[], char *env[])
{
    int thereIsAPipe = 0;
    int pid;
    int returnValue;
    int i = 0;
    while (i != 2)
    {
        int fd[2];
        if (thereIsAPipe == 1)
        {
            pipe(fd);
        }
        pid = fork();
        if (pid == 0) // child process
        {
            if (thereIsAPipe == 1)
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

            char *args[]={"/bin/ls", "./",NULL}; 
            execv(args[0],args); 

        }
        waitpid(pid, &returnValue, 0);
        i++;

    }
    if (returnValue == 256)
        returnValue = 1;
    return (returnValue);
}