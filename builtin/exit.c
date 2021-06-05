/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 18:19:18 by ynoam             #+#    #+#             */
/*   Updated: 2021/04/17 15:39:30 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	ft_exit(char **args)
{
	long long int	j;
	int				i;

	ft_putstr_fd("exit\n", 2);
	if (args[1])
	{
		j = 0;
		while (args[1][j])
		{
			if (((!ft_isdigit(args[1][j]) && args[1][0] != '-') || j >= 19)
					&& put_error("numeric argument required", \
						ft_strjoin("exit: ", args[1])))
				exit(255);
			j++;
		}
		if (args[2] && put_error("too many arguments", "exit"))
			return (1);
		exit(ft_atoi(args[1]));
	}
	exit(0);
	return (0);
}
