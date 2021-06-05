#ifndef EXECUTE_H
# define EXECUTE_H
# include <dirent.h> 
# include "../parsing/datatypes_parsing.h"

char	**create_args(t_cmd *cmd);
int		creat_file_or_openit(char *filename, int trunc);
int		create_files(t_files *files);
int		exec_builtin(t_cmd *cmd, t_env *env);
int		exec_child(int var, int *fd, t_cmd *cmd, t_env *env);
int		exec_child2(t_cmd *cmd, t_env *env);
int		exec_normal(t_cmd *cmd, t_env *env);
int		exec_normal2(t_cmd *cmd, t_env *env);
int		exec_pipe(t_cmd *cmd, t_env *env);
int		execute(t_cmd *cmds, t_env *env, int cmd_return);
int		ft_free_double(char **ptr);
int		is_builtin(char *command);
int		is_path(char *cmd);
int		pipe_count(t_cmd *tmp);
int		put_error(char *errorstr, char *filename);
int		return_value(int ret);
int		wait_for_last_child(int *fd, int pcount, t_cmd *cmd, t_env *env);
t_env	*search_env_for_node(t_env *s_env, char *key);
void	assign_stdin_stdout(char *stdoutf, char *stdinf, int trunc, int *fd);
void	change_stdin_stdout(t_files *files, int *fd);
void	close_fds(int *fd);
void	close_pipe(int fd[]);
void	search_for_path_and_exec(t_cmd *cmd, t_env *env, char **no);
void	change_cmd_args(t_cmd *cmd);
int		open_file_for_read(char *file, int i);

#endif
