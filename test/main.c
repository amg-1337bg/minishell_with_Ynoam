#include <stdio.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
  
int main(void)
{
    // struct dirent *de;  // Pointer for directory entry
  
    // // opendir() returns a pointer of DIR type. 
    // DIR *dr = opendir(".");
  
    // if (dr == NULL)  // opendir returns NULL if couldn't open directory
    // {
    //     printf("Could not open current directory" );
    //     return 0;
    // }
  
    // // for readdir()
    // while ((de = readdir(dr)) != NULL)
    //         printf("%s\n", de->d_name);
  
    // closedir(dr);    
    // return 0;
    char *args[] = {"ls", NULL};
    printf("%d\n", execve("/bin/ls", args, NULL));
    printf("hello\n");
}
