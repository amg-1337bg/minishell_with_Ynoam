#include "gnl/get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/errno.h>
#include "./libft/libft.h"

#define binPath "/bin/pwd"
#define Minishell "minishell > "

typedef struct s_builtins_command
{
    char    *cmd;
    char    **args;
    int     operator;
    char    *fd_file;
    char    *full;
    struct s_builtins_command *next;
}           t_cmd;

typedef struct s_environment
{
    char *key;
    char *value;
    struct s_environment *next;
}               t_env;

t_env   *g_env;
t_cmd   *g_cmd;


t_env	*ft_lstlst(t_env *lst);
void    getenvp(t_env *s_env, char **envp);
void    error();
void    dlt_env(t_env *s_env, char *key);
void    mdf_env(t_env *s_env, char *key, char *value);
void    crt_env(t_env *s_env, char *key, char *value);
void    get_cmd(t_cmd **s_cmd, char *line);
t_cmd	*ft_lstcmd(t_cmd *lst);