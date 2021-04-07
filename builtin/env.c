/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:22:34 by ynoam             #+#    #+#             */
/*   Updated: 2021/04/07 16:16:01 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int		ft_env(t_env *head, int *fd)
{
	while (head)
	{
		if (head->key && head->value)
		{
			if (ft_strncmp(head->key, "_", 1) == 0 && ft_strlen(head->key) == 1)
			{
				ft_putstr_fd("_=env", fd[1]);
				ft_putstr_fd("\n", fd[1]);
			}
			else
			{
				ft_putstr_fd(head->key, fd[1]);
				ft_putstr_fd("=", fd[1]);
				ft_putstr_fd(head->value, fd[1]);
				ft_putstr_fd("\n", fd[1]);
			}
		}
		head = head->next;
	}
	return (0);
}