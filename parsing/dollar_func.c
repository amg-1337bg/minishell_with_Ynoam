/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:57:01 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/05 17:05:03 by bamghoug         ###   ########.fr       */
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

void	dollar_founded(char **str, t_env *s_env, int *i, int just_char)
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
	if (join_dollar_val(str, s_env, i, begin) == 1)
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
	// tmp = value;
	// value = ft_strtrim(value, " ");
	// free(tmp);
	tmp = str[0];
	str[0] = insert_var_value(ft_substr(str[0], 0, *i), value,
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

int	join_dollar_val(char **str, t_env *s_env, int *i, int begin)
{
	char	*value;
	char	*key;
	char	*tmp;

	key = ft_substr(str[0], (*i) + 1, begin - ((*i) + 1));
	if (ft_strlen(key) == 0)
		return (ft_free(&key));
	value = ft_strdup(search_env(s_env, key));
	tmp = value;
	value = ft_strtrim(value, " ");
	free(tmp);
	tmp = str[0];
	str[0] = insert_var_value(ft_substr(str[0], 0, *i), value,
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

char	*insert_var_value(char *after, char *value, char *before)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin(after, value);
	ret = ft_strjoin(tmp, before);
	free(tmp);
	free(after);
	free(before);
	return (ret);
}

int	check_before(char **str, int *i, int begin, int just_char)
{
	if (begin != 0 && str[0][begin - 1] == '\\'
		&& just_char != -2 && just_char != begin - 1)
	{
		rm_char(str, begin - 1);
		*i -= 1;
		return (1);
	}
	return (0);
}
