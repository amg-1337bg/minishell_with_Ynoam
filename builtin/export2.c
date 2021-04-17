/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:05:37 by ynoam             #+#    #+#             */
/*   Updated: 2021/04/17 15:06:05 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	same(char *str1, char *str2)
{
	if (ft_strncmp(str1, str2, ft_strlen(str1)) == 0
		&& ft_strlen(str1) == ft_strlen(str2))
		return (1);
	return (0);
}

void	print(t_env **head, int i, int *fd)
{
	int		j;

	j = 0;
	while (j < i)
	{
		if (head[j]->key && (head[j]->key[0] != '_' || head[j]->key[1] != 0))
		{
			ft_putstr_fd("declare -x ", fd[1]);
			ft_putstr_fd(head[j]->key, fd[1]);
			if (head[j]->value)
			{
				ft_putstr_fd("=", fd[1]);
				ft_putstr_fd("\"", fd[1]);
				ft_putstr_fd(head[j]->value, fd[1]);
				ft_putstr_fd("\"", fd[1]);
				ft_putstr_fd("\n", fd[1]);
			}
			else
				ft_putstr_fd("\n", fd[1]);
		}
		j++;
	}
}

void	swap_env(t_env **arr, int k, int j)
{
	t_env	*tmp;

	tmp = arr[j];
	arr[j] = arr[k];
	arr[k] = tmp;
}

void	sort_env(t_env **arr, int i, int *fd)
{
	int		j;
	int		k;
	int		c;

	j = -1;
	while (++j < i - 1)
	{
		k = j;
		while (++k < i)
		{
			c = 0;
			while (arr[j]->key[c] || arr[k]->key[c])
			{
				if (arr[j]->key[c] > arr[k]->key[c])
				{
					swap_env(arr, k, j);
					break ;
				}
				else if (arr[j]->key[c] < arr[k]->key[c] || arr[j]->key[c] == 0)
					break ;
				c++;
			}
		}
	}
	print(arr, i, fd);
}
