/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 08:53:29 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/05 18:21:49 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_again(t_cmd *cmd)
{
	int		i;
	int		from;
	char	*tmp;

	i = -1;
	from = -1;
	tmp = NULL;
	while (cmd->cmd != NULL && cmd->cmd[++i] != '\0')
	{
		if (cmd->cmd[i] == ' ')
		{
			tmp = cmd->cmd;
			cmd->cmd = ft_substr(cmd->cmd, 0, i);
			look_for_args(cmd, tmp, i);
			free(tmp);
			return ;
		}
	}
}

int	clean_rep_args(t_args *args, t_env *s_env, int cmd_return)
{
	while (args)
	{
		if (special_chars(&args->arg, s_env, cmd_return) != 0)
			return (-1);
		args = args->next;
	}
	return (0);
}

int	clean_rep_files(t_files *file, t_env *s_env, int cmd_return)
{
	char	*tmp;
	int		i;

	i = 0;
	while (file)
	{
		if (file->file[0] == '$')
		{
			tmp = ft_strdup(file->file);
			dollar_founded(&file->file, s_env, &i, 0);
			if (strlen(file->file) == 0)
			{
				file->dollar = 1;
				file->file = tmp;
			}
			else
				free(tmp);
		}
		else if (special_chars(&file->file, s_env, cmd_return) != -1)
			return (-1);
		file = file->next;
	}
	return (0);
}

int	clean_rep_pipe(t_cmd *pipe, t_env *s_env, int cmd_return)
{
	t_args	*tmp_args;
	t_files	*tmp_file;

	if (pipe != NULL)
	{
		if (special_chars(&pipe->cmd, s_env, cmd_return) != 0)
			return (-1);
		tmp_args = pipe->args;
		while (tmp_args)
		{
			if (special_chars(&tmp_args->arg, s_env, cmd_return) != 0)
				return (-1);
			tmp_args = tmp_args->next;
		}
		tmp_file = pipe->files;
		while (tmp_file)
		{
			if (special_chars(&tmp_file->file, s_env, cmd_return) != -1)
				return (-1);
			tmp_file = tmp_file->next;
		}
	}
	return (0);
}

int	clean_replace(t_cmd *s_cmd, t_env *s_env, int cmd_return)
{
	t_args	*tmp_args;
	t_files	*tmp_file;
	t_cmd	*tmp_pipe;

	if (special_chars(&s_cmd->cmd, s_env, cmd_return) != 0)
		return (-1);
	tmp_args = s_cmd->args;
	if (clean_rep_args(tmp_args, s_env, cmd_return) == -1)
		return (-1);
	check_again(s_cmd);
	tmp_file = s_cmd->files;
	if (clean_rep_files(tmp_file, s_env, cmd_return) == -1)
		return (-1);
	tmp_pipe = s_cmd->pipe;
	if (clean_rep_pipe(tmp_pipe, s_env, cmd_return) == -1)
		return (-1);
	return (0);
}
