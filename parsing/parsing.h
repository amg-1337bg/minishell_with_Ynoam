#ifndef PARSING_H
# define PARSING_H

#include "datatypes_parsing.h"

int     g_signal;

t_env	*ft_lstlst(t_env *lst);
void    getenvp(t_env **s_env, char **envp);
void    dlt_env(t_env *s_env, char *key);
void    mdf_env(t_env *s_env, char *key, char *value);
void    crt_env(t_env *s_env, char *key, char *value);
int     get_cmd(t_cmd **s_cmd, t_env *s_env, char *line, int *ret);
char    *search_env(t_env *s_env, char *key);
t_cmd	*ft_lstcmd(t_cmd *lst);
char    **create_envp(t_env *s_env, char *cmd);
int		list_size(t_env *head);

// get_cmd

void    check_quotes(char c, int *quote, int *dquote);
int     quote_detected(char *line, int *j, int just_char);

// redirection.c

int     get_redirection(t_cmd *s_cmd, int *i, int from, int just_char);
char    *get_redir_type(t_cmd *s_cmd, int *i);
char    *get_filename(t_cmd *s_cmd, int *i, int just_char);

// parse_cmd.c
int     cmd_parser(t_cmd **s_cmd, t_env *s_env);
void    get_the_cmd(t_cmd *s_cmd, t_env **s_env);
void    convert_cmd_to_env(t_cmd *s_cmd, t_env **s_env);
void     get_cmd_args(t_cmd *s_cmd, int from, int *i);
char    *get_filename(t_cmd *s_cmd, int *i, int just_char);
char    *get_redir_type(t_cmd *s_cmd, int *i);
int     get_redirection(t_cmd *s_cmd, int *i, int from, int just_char);
int     pipe_function(t_cmd *s_cmd, int *i, int *from, int just_char);
int     get_the_rest(t_cmd *s_cmd, int *i, int from);
int     space_count(char *str);
t_args	*ft_lastarg(t_args *lst);

// free_strcut.c

void    free_cmd(t_cmd **s_cmd);
void    free_files(t_files *s_files);
void    free_args(t_args *s_args);

//terminal.c

void	modify_attr();

// ERRORS
void    printed_errors(int error_code);
void    error();

//  clean_replace.c
void    rm_char(char **str, int char_index);
int     clean_replace(t_cmd *s_cmd, t_env *s_env, int cmd_return);
void    looking_for_dollar(char **str, t_env *s_env, int *from, int *to);
void    dollar_founded(char **str, t_env *s_env, int *i, int just_char);

// Main
char    *get_line(t_line **h_line, struct termios old, int *cmd_return);
void    ctrl_c(int c);


#endif
