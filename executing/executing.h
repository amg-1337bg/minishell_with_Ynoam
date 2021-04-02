<<<<<<< HEAD
#ifndef EXECTING_H
# define EXECTING_H
#include "../parsing/datatypes_parsing.h"

int     execute(t_cmd *cmds, char **env);

=======
#ifndef EXECTING_H
# define EXECTING_H
#include "../parsing/datatypes_parsing.h"
#include <dirent.h> 

void	put_error(char *errorstr,char *filename);
int     execute(t_cmd *cmds, char **env);

>>>>>>> 3bcf84087d2bc0269e1d5297f0b2371b8974bfa2
#endif