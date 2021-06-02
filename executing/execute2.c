/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:33:39 by ynoam             #+#    #+#             */
/*   Updated: 2021/05/26 12:25:13 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	return_value(int ret)
{
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	else if (WIFSTOPPED(ret))
		return (WSTOPSIG(ret));
	else if (WIFSIGNALED(ret))
		return (WTERMSIG(ret));
	return (0);
}

void	close_pipe(int fd[])
{
	close(fd[0]);
	close(fd[1]);
}

char	**create_args(t_cmd *cmd)
{
	t_args	*tmp_args;
	char	**argv;
	int		i;
	int		j;

	tmp_args = cmd->args;
	i = 1;
	while (tmp_args)
	{
		tmp_args = tmp_args->next;
		i++;
	}
	tmp_args = cmd->args;
	argv = malloc((i + 1) * sizeof(char *));
	argv[0] = cmd->cmd;
	j = 1;
	while (j < i)
	{
		argv[j] = tmp_args->arg;
		tmp_args = tmp_args->next;
		j++;
	}
	argv[j] = NULL;
	return (argv);
}

int	create_files(t_files *files)
{
	while (files)
	{
		if (files->file[0] == '$')
			put_error("ambiguous redirect",files->file);
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
