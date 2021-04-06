#ifndef EXECTING_H
# define EXECTING_H
#include "../parsing/datatypes_parsing.h"
#include <dirent.h> 

void	put_error(char *errorstr, char *filename);
int     execute(t_cmd *cmds, t_env *env);
t_env   *search_env_for_node(t_env *s_env, char *key);

#endif