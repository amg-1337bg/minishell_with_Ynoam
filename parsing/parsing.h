#ifndef PARSING_H
# define PARSING_H

#include "datatypes_parsing.h"

t_env	*ft_lstlst(t_env *lst);
void    getenvp(t_env **s_env, char **envp);
void    dlt_env(t_env *s_env, char *key);
void    mdf_env(t_env *s_env, char *key, char *value);
void    crt_env(t_env *s_env, char *key, char *value);
int     get_cmd(t_cmd **s_cmd, t_env *s_env, char *line);
char    *search_env(t_env *s_env, char *key);
t_cmd	*ft_lstcmd(t_cmd *lst);
char    **create_envp(t_env *s_env, char *cmd);

// get_cmd

void    check_quotes(char c, int *quote, int *dquote);

// parse_cmd.c
int     cmd_parser(t_cmd **s_cmd, t_env *s_env);
void    get_the_cmd(t_cmd *s_cmd, t_env **s_env);
void    convert_cmd_to_env(t_cmd *s_cmd, t_env **s_env);
int     get_cmd_args(t_cmd *s_cmd, int from, int *i);

// free_strcut.c

void    free_cmd(t_cmd **s_cmd);
void    free_files(t_files *s_files);
void    free_args(t_args *s_args);

// ERRORS
void    printed_errors(int error_code, char *str);
void    error();
//  clean_replace.c

int    clean_replace(t_cmd *s_cmd, t_env *s_env);
void   looking_for_dollar(char **str, t_env *s_env, int from, int *to);
void   dollar_founded(char **str, t_env *s_env, int *i, int just_char);

#endif