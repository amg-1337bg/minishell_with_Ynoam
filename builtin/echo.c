/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:43:33 by ynoam             #+#    #+#             */
/*   Updated: 2021/06/12 16:07:10 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	ft_echo2(char *argv[], int i, int fd, int flag)
{
	while (argv[1] && argv[i])
	{
		if (argv[i] != NULL && argv[i][0] != 0)
		{
			ft_putstr_fd(argv[i++], fd);
			break ;
		}
		i++;
	}
	while (argv[1] && argv[i])
	{
		if (argv[i] != NULL && argv[i][0] != 0)
		{
			ft_putstr_fd(" ", fd);
			ft_putstr_fd(argv[i], fd);
		}
		i++;
	}
	if (flag == 0)
		ft_putstr_fd("\n", fd);
}

int	ft_echo(char *argv[], int *fd)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = 0;
	while (argv[1] && ++i && argv[i])
	{
		if (ft_strlen(argv[i]) >= 2 && argv[i][0] == '-')
		{
			j = 1;
			while (argv[i][j] == 'n')
				j++;
			if (argv[i][j] == '\0' && ++flag)
				continue ;
			if (argv[i][j] != '\0')
				break ;
		}
		else
			break ;
	}
	ft_echo2(argv, i, fd[1], flag);
	return (0);
}
