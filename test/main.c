#include <stdio.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/errno.h>
#include <string.h>
#include <paths.h>
int main(int ac, char *av[], char *env[])
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
