/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 08:42:54 by bamghoug          #+#    #+#             */
/*   Updated: 2021/03/06 09:09:23 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(t_args *s_args)
{
	t_args	*arg_next;
	t_args	*tmp;

	tmp = s_args;
	while (tmp)
	{
		arg_next = tmp->next;
		free(tmp->arg);
		free(tmp);
		tmp = arg_next;
	}
}

void	free_files(t_files *s_files)
{
	t_files	*file_next;
	t_files	*tmp;

	tmp = s_files;
	while (tmp)
	{
		file_next = tmp->next;
		free(tmp->type);
		free(tmp->file);
		free(tmp);
		tmp = file_next;
	}
}

void	free_pipe(t_cmd **s_cmd)
{
	t_cmd	*cmd_next;
	t_cmd	*tmp;

	tmp = *s_cmd;
	while (tmp)
	{
		cmd_next = tmp->next;
		free(tmp->cmd);
		free_args(tmp->args);
		free_files(tmp->files);
		free(tmp->full);
		free(tmp);
		tmp = cmd_next;
	}
	*s_cmd = NULL;
}

void	free_cmd(t_cmd **s_cmd)
{
	t_cmd	*cmd_next;
	t_cmd	*tmp;

	tmp = *s_cmd;
	while (tmp)
	{
		cmd_next = tmp->next;
		free(tmp->cmd);
		free_args(tmp->args);
		free_files(tmp->files);
		free_pipe(&tmp->pipe);
		free(tmp->full);
		free(tmp);
		tmp = cmd_next;
	}
	*s_cmd = NULL;
}
