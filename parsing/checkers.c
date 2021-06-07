/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 10:30:01 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/07 14:48:48 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checker(t_cmd *s_cmd, int *i, int *from, int *just_char)
{
	if (*from == -1)
		*from = (*i);
	if (s_cmd->full[(*i)] == '\'' || s_cmd->full[(*i)] == '"')
		quote_detected(s_cmd->full, i, *just_char);
	else if (s_cmd->full[(*i)] == '>' || s_cmd->full[(*i)] == '<')
	{
		if (get_redirection(s_cmd, i, *from, *just_char) != 0)
			*from = -1;
	}
	else if (s_cmd->full[(*i)] == ' ' && (*i) > 0 && (s_cmd->full[(*i) - 1] != '\\'
			|| *just_char == (*i) - 1))
	{
		get_cmd_args(s_cmd, *from, i);
		*from = -1;
	}
	else if (s_cmd->full[(*i)] == '|')
	{
		if (pipe_function(s_cmd, i, from, *just_char) < 0)
			return (-1);
	}
	else if (s_cmd->full[(*i)] == '\\' && s_cmd->full[(*i) + 1] == '\\')
		*just_char = (*i) + 1;
	return (0);
}

void	call_get_cmd(t_cmd *pipe_cmd, int *i, int *from)
{
	get_cmd_args(pipe_cmd, (*from), i);
	(*from) = -1;
}

int	pipe_checker(t_cmd *pipe_cmd, int *i, int *from, int *just_char)
{
	if ((*from) == -1)
		(*from) = (*i);
	if (pipe_cmd->full[*i] == '\'' || pipe_cmd->full[*i] == '"')
		quote_detected(pipe_cmd->full, i, *just_char);
	else if ((pipe_cmd->full[*i] == '>' || pipe_cmd->full[*i] == '<')
		&& get_redirection(pipe_cmd, i, (*from), *just_char) != 0)
		(*from) = -1;
	else if (pipe_cmd->full[*i] == ' ' && (pipe_cmd->full[(*i) - 1] != '\\'
			|| *just_char == (*i) - 1))
		call_get_cmd(pipe_cmd, i, from);
	else if (pipe_cmd->full[(*i)] == '|' && (pipe_cmd->full[(*i) - 1] != '\\'
			|| *just_char == (*i) - 1))
	{
		if ((*from) == (*i))
		{
			(*from) = -1;
			(*i) -= 1;
		}
		return (1);
	}
	else if (pipe_cmd->full[*i] == '\\' && pipe_cmd->full[(*i) + 1] == '\\')
		(*just_char) = (*i) + 1;
	return (0);
}
