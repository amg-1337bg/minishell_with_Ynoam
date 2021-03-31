#include <stdio.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/errno.h>
#include <string.h>
int main(void)
{
	printf("%d\n", open("file99", O_RDONLY));
	write (2, strerror(errno), strlen(strerror(errno)));
	write (2, "\n", 1);
	//printf("%d\n", close(-1));
     return 0;
}
