/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:37:13 by bamghoug          #+#    #+#             */
/*   Updated: 2021/04/04 1 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	crt_env(t_env *s_env, char *key, char *value)
{
	t_env	*fill;
	t_env	*tmp;

	fill = malloc(sizeof(t_env));
	fill->key = key;
	fill->value = value;
	fill->next = NULL;
	tmp = ft_lstlst(s_env);
	if (tmp == NULL)
		s_env = fill;
	else
		tmp->next = fill;
}

void	mdf_env(t_env *s_env, char *key, char *value)
{
	t_env	*tmp;
	int		found;

	tmp = s_env;
	found = 0;
	while (tmp)
	{
		if (tmp->key && ft_strncmp(tmp->key, key, ft_strlen(key)) == 0
			&& ft_strlen(key) == ft_strlen(tmp->key))
		{
			free(tmp->value);
			tmp->value = value;
			found = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (found != 1)
		crt_env(s_env, key, value);
}

void	dlt_env(t_env *s_env, char *key)
{
	t_env	*first;
	t_env	*second;

	first = s_env;
	while (first)
	{
		second = first->next;
		if (second != NULL && second->key && ft_strncmp(second->key, key, ft_strlen(key)) == 0
			&& ft_strlen(key) == ft_strlen(second->key))
		{
			first->next = second->next;
			free(second->key);
			free(second->value);
			free(second);
			return ;
		}
		else if (first->key && ft_strncmp(first->key, key, ft_strlen(key)) == 0
			&& ft_strlen(key) == ft_strlen(first->key))
		{
			free(first->key);
			free(first->value);
			s_env = first->next;
			free(first);
			return ;
		}
		first = first->next;
	}
}

char	*search_env(t_env *s_env, char *key)
{
	t_env	*tmp;

	tmp = s_env;
	while (tmp)
	{
		if (tmp->key && !ft_strncmp(tmp->key, key, ft_strlen(tmp->key))
			&& ft_strlen(tmp->key) == ft_strlen(key))
		{
			if (tmp->value == NULL)
				return ("");
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return ("");
}

t_env	*search_env_for_node(t_env *s_env, char *key)
{
	t_env	*tmp;

	tmp = s_env;
	while (tmp)
	{
		if (tmp->key && !ft_strncmp(tmp->key, key, ft_strlen(tmp->key))
			&& ft_strlen(tmp->key) == ft_strlen(key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
