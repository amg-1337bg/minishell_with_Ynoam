/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_func1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 14:35:52 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/07 14:40:16 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_inside(char **str, t_env *s_env, int *i, int just_char)
{
	int		begin;
	char	*value;
	char	*key;
	char	*tmp;

	begin = *i;
	if (check_before(str, i, begin, just_char) == 1)
		return ;
	while (str[0][++begin] != '\0')
	{
		if (ft_isalnum(str[0][begin]) != 1 && str[0][begin] != '_')
			break ;
	}
	if (join_dollar_in(str, s_env, i, begin) == 1)
		return ;
	(*i) -= 1;
}

int	join_dollar_in(char **str, t_env *s_env, int *i, int begin)
{
	char	*value;
	char	*key;
	char	*tmp;

	key = ft_substr(str[0], (*i) + 1, begin - ((*i) + 1));
	if (ft_strlen(key) == 0)
		return (ft_free(&key));
	value = ft_strdup(search_env(s_env, key));
	tmp = str[0];
	str[0] = insvalue(ft_substr(str[0], 0, *i), value,
			ft_strdup(&str[0][begin]));
	free(tmp);
	if (ft_strlen(value) != 0)
	{
		(*i) += ft_strlen(value);
		if ((*i) < 0)
			(*i) *= -1;
	}
	free(key);
	free(value);
	return (0);
}

char	*join_splited_val(char **str)
{
	char	*ret;
	char	*tmp;
	int		i;

	i = -1;
	ret = ft_strdup("");
	while (str[++i] != NULL)
	{
		tmp = ret;
		ret = ft_strjoin(ret, str[i]);
		free(tmp);
		if (str[i + 1] != NULL)
		{
			tmp = ret;
			ret = ft_strjoin(ret, " ");
			free(tmp);
		}
	}
	if (ft_strlen(ret) == 0)
	{
		tmp = ret;
		ret = ft_strdup(" ");
		free(tmp);
	}
	return (ret);
}
