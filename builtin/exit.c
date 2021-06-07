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

long long int	ft_atoll(const char *str, int *myerror)
{
	int				i;
	long long int	number;
	int				sign;
	int				test;

	i = 0;
	number = 0;
	sign = 1;
	test = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32 || str[i] == '0')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] == '0')
		i++;
	while (str[i] >= 48 && str[i] <= 57 && ++test)
		number = (number * 10) + str[i++] - 48;
	if ((test > 19 && sign == 1) || (test > 20 && sign == -1))
		*myerror = 1;
	else
		*myerror = 0;
	return (number * sign);
}

int	ft_exit(char **args)
{
	long long int	j;
	int				i;
	int				myerror;

	ft_putstr_fd("exit\n", 2);
	if (args[1])
	{
		j = 0;
		while (args[1][j])
		{
			if (!ft_isdigit(args[1][j] && args[1][0] != '-')
					&& put_error("numeric argument required", \
						ft_strjoin("exit: ", args[1])))
				exit(255);
			j++;
		}
		if (args[2] && put_error("too many arguments", "exit"))
			return (1);
		j = ft_atoll(args[1], &myerror);
		printf(">>>>>>>>>>>>>>>>>> %lld\n", j);
		if (myerror || (args[1][0] == '-' && j == 9223372036854775807) || (args[1][0] != '-' && (j == -9223372036854775808 || j == -9223372036854775807)))
		{
			put_error("numeric argument required", ft_strjoin("exit: ", args[1]));
			exit(255);
		}
		exit(j);
	}
	exit(0);
	return (0);
}
