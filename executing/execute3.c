/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:35:27 by ynoam             #+#    #+#             */
/*   Updated: 2021/04/20 15:35:32 by ynoam            ###   ########.fr       */
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

int	exec_builtin(t_cmd *cmd, t_env *env)
{
	int	*fd;
	int	ret;

	fd = malloc(sizeof(int) * 2);
	ret = 0;
	change_stdin_stdout(cmd->files, fd);
	if (!ft_strncmp(cmd->cmd, "echo", ft_strlen("echo") + 1))
		ret = ft_echo(create_args(cmd), fd);
	else if (!ft_strncmp(cmd->cmd, "cd", ft_strlen("cd") + 1))
		ret = cd(env, cmd->args);
	else if (!ft_strncmp(cmd->cmd, "pwd", ft_strlen("pwd") + 1))
		ret = pwd(fd);
	else if (!ft_strncmp(cmd->cmd, "export", ft_strlen("export") + 1))
		ret = export(env, create_args(cmd), fd);
	else if (!ft_strncmp(cmd->cmd, "unset", ft_strlen("unset") + 1))
		ret = unset(env, create_args(cmd));
	else if (!ft_strncmp(cmd->cmd, "env", ft_strlen("env") + 1))
		ret = ft_env(env, fd);
	else if (!ft_strncmp(cmd->cmd, "exit", ft_strlen("exit") + 1))
		ret = ft_exit(create_args(cmd));
	close_fds(fd);
	return (ret);
}

int	is_path(char *cmd)
{
	int	i;

	i = ft_strlen(cmd);
	if ((i >= 2 && cmd[0] == '.' && cmd[1] == '/') || (i >= 3 && cmd[0] == '.' && \
				cmd[1] == '.' && cmd[2] == '/') || (i >= 1 && cmd[0] == '/'))
		return (1);
	return (0);
}

int	exec_normal2(t_cmd *cmd, t_env *env)
{
	int	*fd;
	DIR	*dir;

	fd = malloc(sizeof(int) * 2);
	dir = opendir(cmd->cmd);
	if (dir)
	{
		put_error("is a directory", cmd->cmd);
		closedir(dir);
		free(fd);
		return (126);
	}
	else
	{
		change_stdin_stdout(cmd->files, fd);
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		execve(cmd->cmd, create_args(cmd), create_envp(env, cmd->cmd));
		put_error(strerror(errno), cmd->cmd);
		free(fd);
		return (127);
	}
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
