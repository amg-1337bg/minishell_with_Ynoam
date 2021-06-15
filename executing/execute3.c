/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:35:27 by ynoam             #+#    #+#             */
/*   Updated: 2021/06/12 15:35:05 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	close_fds(int *fd)
{
	if (fd[0] != 0)
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
	free(fd);
}

int	exec_builtin(t_cmd *cmd, t_env *env, int ret1)
{
	int		*fd;
	int		ret;
	char	**arg;

	fd = malloc(sizeof(int) * 2);
	ret = 0;
	change_stdin_stdout(cmd->files, fd);
	arg = create_args(cmd);
	if (!ft_strncmp(cmd->cmd, "echo", ft_strlen("echo") + 1))
		ret = ft_echo(arg, fd);
	else if (!ft_strncmp(cmd->cmd, "cd", ft_strlen("cd") + 1))
		ret = cd(env, cmd->args);
	else if (!ft_strncmp(cmd->cmd, "pwd", ft_strlen("pwd") + 1))
		ret = pwd(fd);
	else if (!ft_strncmp(cmd->cmd, "export", ft_strlen("export") + 1))
		ret = ft_export(env, arg, fd);
	else if (!ft_strncmp(cmd->cmd, "unset", ft_strlen("unset") + 1))
		ret = unset(env, arg);
	else if (!ft_strncmp(cmd->cmd, "env", ft_strlen("env") + 1))
		ret = ft_env(env, fd);
	else if (!ft_strncmp(cmd->cmd, "exit", ft_strlen("exit") + 1))
		ret = ft_exit(arg, ret1);
	close_fds(fd);
	free(arg);
	return (ret);
}

int	is_path(char *cmd)
{
	int	i;

	i = ft_strlen(cmd);
	if ((i >= 2 && cmd[0] == '.' && cmd[1] == '/')
		|| (i >= 3 && cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/')
		|| (i >= 1 && cmd[0] == '/'))
		return (1);
	return (0);
}

int	exec_normal2(t_cmd *cmd, t_env *env)
{
	int		*fd;
	DIR		*dir;
	char	*underscor;

	underscor = find_underscor(cmd);
	fd = malloc(sizeof(int) * 2);
	dir = opendir(cmd->cmd);
	if (dir)
	{
		put_error("is a directory", cmd->cmd);
		closedir(dir);
		free(fd);
		return (126);
	}
	change_stdin_stdout(cmd->files, fd);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	execve(cmd->cmd, create_args(cmd), create_envp(env, underscor));
	put_error(strerror(errno), cmd->cmd);
	free(fd);
	if (errno == 13)
		return (126);
	return (127);
}

int	ft_free_double(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		ft_free(&(ptr[i]));
		i++;
	}
	free(ptr[i]);
	free(ptr);
	return (1);
}
