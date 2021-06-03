/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:21:39 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/03 15:44:57 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*fill_cmd_struct(char *line, int *begin, int end)
{
	t_cmd	*ret;
	char	*str;
	char	*tmp;

	str = ft_substr(line, *begin, end - (*begin));
	tmp = str;
	str = ft_strtrim(str, " ");
	free(tmp);
	if (ft_strlen(str) == 0)
	{
		printed_errors(Syntax_error);
		return (NULL);
	}
	ret = malloc(sizeof(t_cmd));
	if (ret == NULL)
		error();
	ret->cmd = NULL;
	ret->args = NULL;
	ret->files = NULL;
	ret->full = str;
	ret->pipe = NULL;
	ret->next = NULL;
	*begin = end;
	return (ret);
}

t_cmd	*get_full_cmd(char *line, int *i)
{
	int		j;
	int		just_char;
	t_cmd	*ret;

	j = *i;
	ret = NULL;
	just_char = -1;
	while (line[j] != '\0')
	{
		if ((line[j] == 39 || line[j] == 34)
			&& quote_detected(line, &j, just_char) == 0)
			return (0);
		else if (line[j] == ';' && j == 0)
		{
			printed_errors(Syntax_error);
			return (0);
		}
		else if (line[j] == ';' && (line[j - 1] != '\\' || just_char == j - 1))
			break ;
		else if (line[j] == '\\' && line[j + 1] == '\\')
			just_char = j + 1;
		j++;
	}
	ret = fill_cmd_struct(line, i, j);
	return (ret);
}

int	get_cmd(t_cmd **s_cmd, t_env *s_env, char *line, int *ret)
{
	t_cmd	*tmp;
	t_cmd	*last;
	int		i;

	i = 0;
	line = ft_strtrim(line, " ");
	while (line[i] != '\0')
	{
		tmp = get_full_cmd(line, &i);
		if (tmp == NULL)
		{
			*ret = 258;
			return (-1);
		}
		last = ft_lstcmd(s_cmd[0]);
		if (last == NULL)
			s_cmd[0] = tmp;
		else
			last->next = tmp;
		if (line[i] == ';')
			i++;
	}
	if (cmd_parser(s_cmd, s_env) != 0)
		return (-1);
	return (0);
}
