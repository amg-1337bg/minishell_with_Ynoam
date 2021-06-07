/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 17:00:24 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/07 16:36:28 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	found_dquote(char **s, t_env *s_env, int *dquote_ind)
{
	int	i;
	int	just_char;

	i = *dquote_ind;
	just_char = -1;
	while (s[0][++i] != '\0')
	{
		if ((*s)[i] == 34 && i != 0 && (*s)[i - 1] == 92 && just_char != i - 1)
			rm_char(s, --i);
		else if (s[0][i] == '"')
		{
			rm_char(s, i);
			rm_char(s, *dquote_ind);
			*dquote_ind = i - 2;
			return (0);
		}
		else if (s[0][i] == '\\' && s[0][i + 1] == '\\')
		{
			rm_char(s, i);
			just_char = i;
		}
		else if (s[0][i] == '$')
			dollar_inside(s, s_env, &i, just_char);
	}
	return (0);
}

int	found_quote(char **str, int *quote_ind)
{
	int	i;

	i = *quote_ind;
	while (str[0][++i] != '\0')
	{
		if (str[0][i] == '\'')
		{
			rm_char(str, i);
			rm_char(str, *quote_ind);
			*quote_ind = i - 2;
			return (0);
		}
	}
	return (-1);
}

void	rm_char(char **str, int char_index)
{
	char	*tmp;
	char	*tmp1;
	char	*tmp3;

	tmp = *str;
	if (char_index == 0)
		*str = ft_strdup(&tmp[char_index + 1]);
	else
	{
		*str = ft_substr(*str, 0, char_index);
		tmp1 = *str;
		tmp3 = ft_strdup(&tmp[char_index + 1]);
		*str = ft_strjoin(*str, tmp3);
		free(tmp1);
		free(tmp3);
	}
	free(tmp);
}

void	char_remove(char **str, int *i, int *just_char)
{
	if (str[0][*i] == '\\')
	{
		rm_char(str, (*i));
		(*just_char) = (*i);
	}
	else
	{
		rm_char(str, (*i) - 1);
		(*i) -= 1;
	}
}
