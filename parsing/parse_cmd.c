/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:31:59 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/07 11:08:38 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	space_count(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	return (i);
}

void	get_cmd_args(t_cmd *s_cmd, int from, int *i)
{
	t_args	*args;
	t_args	*tmp_arg;
	char	*str;

	str = ft_substr(s_cmd->full, from, (*i) - from);
	if (s_cmd->cmd == NULL)
		s_cmd->cmd = str;
	else
	{
		args = (t_args *)malloc(sizeof(t_args));
		args->arg = str;
		args->next = NULL;
		tmp_arg = ft_lastarg(s_cmd->args);
		if (tmp_arg == NULL)
			s_cmd->args = args;
		else
			tmp_arg->next = args;
	}
	*i += space_count(&s_cmd->full[*i]) - 1;
}

int	get_the_rest(t_cmd *s_cmd, int *i, int from)
{
	if (from != -1)
		get_cmd_args(s_cmd, from, i);
	return (0);
}

int	get_args(t_cmd *s_cmd)
{
	int		i;
	int		from;
	int		just_char;

	i = -1;
	from = -1;
	just_char = -1;
	while (s_cmd->full[++i] != '\0')
	{
		if (checker(s_cmd, &i, &from, &just_char) < 0)
			return (-1);
	}
	get_the_rest(s_cmd, &i, from);
	return (0);
}

int	cmd_parser(t_cmd **s_cmd, t_env *s_env)
{
	t_cmd	*tmp;
	int		error;
	char	*tofree;
	char	*i;

	tmp = s_cmd[0];
	while (tmp)
	{
		tofree = tmp->full;
		tmp->full = ft_strtrim(tmp->full, " ");
		free(tofree);
		error = get_args(tmp);
		if (error != 0)
			return (error);
		tmp = tmp->next;
	}
	return (0);
}
