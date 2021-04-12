/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:43:33 by ynoam             #+#    #+#             */
/*   Updated: 2021/04/07 15:44:10 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int		ft_echo(char *argv[], int *fd)
{
	int i;
	int j;
	int flag;

	flag = 0;
	i = 1;
	while (argv[1] && argv[i])
	{
		j = 1;
		if (ft_strlen(argv[i]) > 2 && argv[i][0] == '-')
		{
			while (argv[i][j] == 'n')
				j++;
			if (argv[i][j] == '\0')
				flag = 1;
			if (argv[i][j] != '\0')
				break;
		}
		else
			break;
		i++;
	}
	while(argv[1] && argv[i])
	{
		ft_putstr_fd(argv[i], fd[1]);
		if (argv[i + 1] != NULL)
			ft_putstr_fd(" ", fd[1]);
		i++;
	}
	if (flag == 0)
		ft_putstr_fd("\n", fd[1]);
	return (0);
}
