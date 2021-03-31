/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:44:48 by ynoam             #+#    #+#             */
/*   Updated: 2021/03/31 19:14:30 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int i;
	int number;
	int sign;
	int test;

	i = 0;
	number = 0;
	sign = 1;
	test = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= 48 && str[i] <= 57 && ++test)
		number = (number * 10) + str[i++] - 48;
	if (test > 10 && sign == 1)
		return (-1);
	if (test > 10 && sign == -1)
		return (0);
	return (number * sign);
}
