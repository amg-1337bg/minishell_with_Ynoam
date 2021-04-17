#ifndef BUILTIN_H
# define BUILTIN_H
# include "../parsing/minishell.h"

int		pwd(int *fd);
int		ft_exit(char **args);
int		ft_echo(char *argv[], int *fd);
int		ft_env(t_env *head, int *fd);
int		unset(t_env *head, char *argv[]);
int		export(t_env *head, char *argv[], int *fd);
int		same(char *str1, char *str2);
void	print(t_env **head, int i, int *fd);
void	swap_env(t_env **arr, int k, int j);
void	sort_env(t_env **arr, int i, int *fd);
int		cd(t_env *env, t_args *args);

#endif
