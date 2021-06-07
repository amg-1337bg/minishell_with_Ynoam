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
void    looking_for_dollar(char **str, t_env *s_env, int from, int *to);
void    dollar_founded(char **str, t_env *s_env, int *i, int just_char);

// Main
char    *get_line(t_line **h_line, int *cmd_return);
void    ctrl_c(int c);

// pipe.c
int     pipe_function(t_cmd *s_cmd, int *i, int *from, int just_char);
int     get_pipe_cmd(t_cmd *s_cmd, int *i);
int     pipe_checker(t_cmd *pipe_cmd, int *i, int *from, int *just_char);
void    initializ_pipecmd(t_cmd **pipe_cmd, t_cmd *s_cmd);

// linked_list.c
t_args	*ft_lastarg(t_args *lst);
t_files	*ft_lastfile(t_files *lst);
t_env	*ft_lstlst(t_env *lst);
t_cmd	*ft_lstcmd(t_cmd *lst);
t_line	*last_line(t_line *head);

//env.c

void    getenvp(t_env **s_env, char **envp);
void    changenvp(t_env *env);
char **create_envp(t_env *s_env, char *cmd);

//quotes.c
int     quote_detected(char *line, int *j, int just_char);
int     dquote_traitement(char *line, int *j, char c, int just_char);
int     quote_traitement(char *line, int *j, char c);
int     quotes_function(char **str, t_env *s_env, int *i, int just_char);

//quotes1.c
int    found_dquote(char **str, t_env *s_env, int *dquote_ind);
int    found_quote(char **str, int *quote_ind);
void    rm_char(char **str, int char_index);
void    char_remove(char **str, int *i, int *just_char);
//dollar.c
char    *insvalue(char *after, char *value, char *before);
int     join_dollar_val(char **str, t_env *s_env, int *i, int begin);
void    dollar_founded(char **str, t_env *s_env, int *i, int just_char);
int     check_before(char **str, int *i, int begin, int just_char);
void	dollar_inside(char **str, t_env *s_env, int *i, int just_char);
int     join_dollar_in(char **str, t_env *s_env, int *i, int begin);
char	*join_splited_val(char **str);

//clean_rep_utils.c
void special_checker(char **str, int *i, int cmd_return, int *just_char);
char *dollar_status(char *str, int *i, int cmd_return);
int special_chars(char **str, t_env **s_env, int cmd_return);
t_args *arg_to_head(t_args *arg, char *cmd, int from, int *i);
void look_for_args(t_cmd *cmd, char *tmp, int i);

unsigned char   gtc(void);
char *char_join(char *str, char c);
void	del_write(char *line);
void	add_to_history(t_line **h_line ,char *line);
void	del_char(char **line);

void    ctrl_c(int c);
void    check_signal(char **line, int *cmd_return);
void    ctrl_b(int c);
void    check_cmd_ret(int *cmd_return);

void    handle_up(t_line **h_line, char **line, char **current);
void    handle_down(t_line **h_line, char **line, char **current);
void    handle_nl(t_line **h_line, char **line);

int     checker(t_cmd *s_cmd, int *i, int *from, int *just_char);
int     pipe_checker(t_cmd *pipe_cmd, int *i, int *from, int *just_char);
void	call_get_cmd(t_cmd *pipe_cmd, int *i, int *from);

#endif
