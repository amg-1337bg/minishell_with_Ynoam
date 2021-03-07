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
        pid = fork();
        if (pid == 0) // child process
        {
            if (thereIsAPipe == 1)
            {
                int fd[2];
                pipe(fd);
                close(fd[0]);
            }
            char *args[]={"/bin/ls", "lklkjlklkj",NULL}; 
            execv(args[0],args); 

        }
        else // parent process
        {
            waitpid(pid, &returnValue, 0);
            i++;
        }
    }
    if (returnValue == 256)
        returnValue = 1;
    return (returnValue);
}