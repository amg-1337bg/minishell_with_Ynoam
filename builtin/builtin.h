#ifndef BUILTIN_H
# define BUILTIN_H
#include "../parsing/minishell.h"

int     pwd(int *fd);
int     ft_exit(char **args);
int		ft_echo(char *argv[], int *fd);
int     ft_env(t_env *head, int *fd);

#endif