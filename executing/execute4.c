/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:36:45 by ynoam             #+#    #+#             */
/*   Updated: 2021/04/20 15:36:48 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	search_for_path_and_exec(t_cmd *cmd, t_env *env, char **fuckyou)
{
	char	**paths;
	char	**argv;
	char	*str2;
	int		i;
	char	*two[2];

	two[1] = find_underscor(cmd);
	i = 0;
	paths = ft_split(search_env(env, "PATH"), ':');
	argv = create_args(cmd);
	str2 = ft_strjoin("/", cmd->cmd);
	while (paths[i])
	{
		two[0] = ft_strjoin(paths[i], str2);
		fuckyou = create_envp(env, two[1]);
		execve(two[0], argv, fuckyou);
		free(two[0]);
		ft_free_double(fuckyou);
		i++;
	}
	put_error("command not found", cmd->cmd);
	ft_free_double(paths);
	ft_free_double(argv);
	ft_free(&str2);
}

int	exec_normal(t_cmd *cmd, t_env *env)
{
	int		*fd;

	if (is_path(cmd->cmd))
		return (exec_normal2(cmd, env));
	fd = malloc(sizeof(int) * 2);
	change_stdin_stdout(cmd->files, fd);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	search_for_path_and_exec(cmd, env, NULL);
	free(fd);
	return (127);
}

int	pipe_count(t_cmd *tmp)
{
	int		i;
	t_cmd	*command;

	command = tmp;
	i = 0;
	command = command->pipe;
	while (command)
	{
		command = command->next;
		i++;
	}
	return (i);
}

int	exec_child2(t_cmd *cmd, t_env *env)
{
	int	one;

	if (cmd->cmd && is_builtin(cmd->cmd))
	{
		one = create_files(cmd->files);
		if (one != 0)
			exit(one);
		exit(exec_builtin(cmd, env));
	}
	else if (cmd->cmd && !is_builtin(cmd->cmd))
	{
		one = create_files(cmd->files);
		if (one != 0)
			exit(one);
		exit(exec_normal(cmd, env));
	}
	else if (cmd->cmd == NULL)
		exit(create_files(cmd->files));
	return (0);
}

int	exec_child(int var, int *fd, t_cmd *cmd, t_env *env)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (var == 0)
		{
			dup2(fd[1], 1);
			close(fd[1]);
		}
		if (var != 0 && var != -1)
		{
			dup2(var, 0);
			dup2(fd[1], 1);
			close(fd[1]);
			close(var);
		}
		if (var == -1)
			dup2(fd[0], 0);
		close(fd[0]);
		exec_child2(cmd, env);
	}
	return (pid);
}
