/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:50:12 by ynoam             #+#    #+#             */
/*   Updated: 2021/04/16 17:32:01 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	unset(t_env *head, char *argv[])
{
	int	i;
	int	j;

	j = 1;
	while (argv[j])
	{
		i = 0;
		if ((!ft_isalpha(argv[j][i]) && argv[j][i] != '_'))
		{
			there_is_an_error(argv[j], 1);
			j++;
			continue ;
		}
		i++;
		while (argv[j][0] != 0 && argv[j][i])
		{
			if ((!ft_isalnum(argv[j][i]) && argv[j][i] != '_')
				&& there_is_an_error(argv[j], 1))
				break ;
			i++;
		}
		dlt_env(head, argv[j]);
		j++;
	}
	return (0);
}
