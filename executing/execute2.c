/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:33:39 by ynoam             #+#    #+#             */
/*   Updated: 2021/06/10 18:36:13 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	return_value(int ret)
{
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	else if (WIFSIGNALED(ret))
	{
		g_signal = 0;
		return (128 + WTERMSIG(ret));
	}
	else if (WIFSTOPPED(ret))
		return (WSTOPSIG(ret));
	return (0);
}

void	close_pipe(int fd[])
{
	close(fd[0]);
	close(fd[1]);
}

char	**create_args(t_cmd *cmd)
{
	t_args	*tmp;
	char	**arg;
	int		i;
	int		j;

	tmp = cmd->args;
	i = 1;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	tmp = cmd->args;
	arg = malloc((i + 1) * sizeof(char *));
	arg[0] = cmd->cmd;
	j = 1;
	while (j < i)
	{
		arg[j] = tmp->arg;
		tmp = tmp->next;
		j++;
	}
	arg[j] = NULL;
	return (arg);
}

int	create_files(t_files *files)
{
	while (files)
	{
		if (files->file[0] == '$' && files->dollar == 1)
			put_error("ambiguous redirect", files->file);
		else if (files->type[0] == '>')
		{
			if (creat_file_or_openit(files->file, 0) == -1)
			{
				put_error(strerror(errno), files->file);
				return (1);
			}
		}
		else if (files->type[0] == '<')
		{
			if (open_file_for_read(files->file, 1) == -1)
			{
				put_error(strerror(errno), files->file);
				return (1);
			}
		}
		files = files->next;
	}
	return (0);
}

int	is_builtin(char *command)
{
	if (!ft_strncmp(command, "echo", ft_strlen("echo") + 1))
		return (1);
	else if (!ft_strncmp(command, "cd", ft_strlen("cd") + 1))
		return (1);
	else if (!ft_strncmp(command, "pwd", ft_strlen("pwd") + 1))
		return (1);
	else if (!ft_strncmp(command, "export", ft_strlen("export") + 1))
		return (1);
	else if (!ft_strncmp(command, "unset", ft_strlen("unset") + 1))
		return (1);
	else if (!ft_strncmp(command, "env", ft_strlen("env") + 1))
		return (1);
	else if (!ft_strncmp(command, "exit", ft_strlen("exit") + 1))
		return (1);
	return (0);
}
