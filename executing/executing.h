#ifndef EXECTING_H
# define EXECTING_H
#include "../parsing/datatypes_parsing.h"
#include <dirent.h> 

void	put_error(char *errorstr,char *filename);
int     execute(t_cmd *cmds, char **env);

#endif