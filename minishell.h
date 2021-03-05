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

typedef struct s_operator{
    char *type; // ">" or ">>" or "<"
    char *file;
    struct s_operator *next;
}              t_files;

typedef struct s_args
{
    char *arg;
    struct s_args *next;
}               t_args;


typedef struct s_command
{
    char    *cmd;
    t_args  *args;
    t_files *files;
    char    *full;
    int     pipe;
    struct s_command *next;
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
void    getenvp(t_env **s_env, char **envp);
void    error();
void    dlt_env(t_env *s_env, char *key);
void    mdf_env(t_env *s_env, char *key, char *value);
void    crt_env(t_env *s_env, char *key, char *value);
void    get_cmd(t_cmd **s_cmd, t_env **s_env, char *line);
char    *search_env(t_env *s_env, char *key);
t_cmd	*ft_lstcmd(t_cmd *lst);
char    **create_envp(t_env *s_env);

// get_cmd

void    check_quotes(char c, int *quote, int *dquote);

// parse_cmd.c
void    cmd_parser(t_cmd **s_cmd, t_env **s_env);
void    get_the_cmd(t_cmd *s_cmd, t_env **s_env);
void    convert_env_to_cmd(t_cmd *s_cmd, t_env **s_env);