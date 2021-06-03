/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:09:18 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/03 19:31:46 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_detected(char *line, int *j, int just_char)
{
	char	c;

	c = line[(*j)];
	if ((*j) != 0 && line[(*j) - 1] == '\\' && just_char != (*j) - 1)
		return (1);
	else
	{
		if (c == '\'')
		{
			if (quote_traitement(line, j, c) == 1)
				return (1);
		}
		else
		{
			if (dquote_traitement(line, j, c, just_char) == 1)
				return (1);
		}
	}
	printf("ERROR: No Multiline Commands\n");
	return (0);
}

int	dquote_traitement(char *line, int *j, char c, int just_char)
{
	while (line[++(*j)] != '\0')
	{
		if (line[(*j)] == '\\' && line[(*j) + 1] == '\\')
			just_char = (*j) + 1;
		else if (line[*j] == '"')
		{
			if (line[(*j) - 1] == '\\' && just_char == (*j) - 1)
				return (1);
			else if (line[(*j) - 1] != '\\')
				return (1);
		}
	}
	return (0);
}

int	quote_traitement(char *line, int *j, char c)
{
	while (line[++(*j)] != '\0')
	{
		if (line[*j] == c)
			return (1);
	}
	return (0);
}

int	quotes_function(char **str, t_env *s_env, int *i, int just_char)
{
	if ((*i) != 0 && str[0][(*i) - 1] == '\\' && just_char != (*i) - 1)
	{
		rm_char(str, (*i) - 1);
		(*i) -= 1;
	}
	else
	{
		if (str[0][(*i)] == '"')
		{
			if (found_dquote(str, s_env, i) == -1)
				return (-1);
		}
		else
		{
			if (found_quote(str, i) == -1)
				return (-1);
		}
	}
	return (0);
}
