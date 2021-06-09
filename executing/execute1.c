/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:30:47 by ynoam             #+#    #+#             */
/*   Updated: 2021/04/20 15:32:24 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

char	*find_underscor(t_cmd *cmd)
{
	t_args	*arg;
	char	*underscor;

	underscor = cmd->cmd;
	arg = cmd->args;
	while (arg)
	{
		underscor = arg->arg;
		arg = arg->next;
	}
	return (underscor);
}

int	creat_file_or_openit(char *filename, int trunc)
{
	return (open(filename, O_WRONLY | O_CREAT | trunc, 00644));
}

int	open_file_for_read(char *filename, int i)
{
	int	j;

	if (i == 1)
	{
		j = open(filename, O_RDONLY);
		if (j == -1)
			return (-1);
		close(j);
	}
	return (open(filename, O_RDONLY));
}

void	assign_stdin_stdout(char *stdoutf, char *stdinf, int trunc, int *fd)
{
	if (stdoutf && !trunc)
		fd[1] = creat_file_or_openit(stdoutf, O_TRUNC);
	else if (stdoutf && trunc)
		fd[1] = creat_file_or_openit(stdoutf, O_APPEND);
	else if (stdinf)
		fd[0] = open_file_for_read(stdinf, 0);
}

void	change_stdin_stdout(t_files *files, int *fd)
{
	char	*stdin_file;
	char	*stdout_file;
	int		trunc;

	fd[0] = 0;
	fd[1] = 1;
	trunc = 0;
	stdout_file = NULL;
	stdin_file = NULL;
	while (files)
	{
		if (files->type[0] == '>' && files->type[1] == 0)
		{
			trunc = 0;
			stdout_file = files->file;
		}
		else if (files->type[0] == '>' && files->type[1] == '>' && ++trunc)
			stdout_file = files->file;
		else if (files->type[0] == '<')
			stdin_file = files->file;
		files = files->next;
	}
	assign_stdin_stdout(stdout_file, stdin_file, trunc, fd);
}
