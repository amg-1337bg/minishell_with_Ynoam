/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:43:33 by ynoam             #+#    #+#             */
/*   Updated: 2021/03/05 17:55:00 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int echo(int argc, char *argv[])
{
	int i;
	int flag;

	i = 1;
	flag = 0;
	if (argc == 1)
	{
		write(1, "\n", 1);
		return (0);
	}
	if (argv[1][0] == '-' && argv[1][1] == 'n' && ++flag)
		i++;
	while (i < argc - 1)
	{
		ft_putstr_fd(argv[i++], 1);
		ft_putstr_fd(" ", 1);
	}
	ft_putstr_fd(argv[i], 1);
	if (flag == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
