/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 21:28:24 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/10 18:33:50 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int c)
{
	c = SIGINT;
	write(1, "\n", 1);
	g_signal = 1;
}

void	check_signal(char **line, int *cmd_return)
{
	char	*cap;

	if (g_signal == 1)
	{
		free(*line);
		*line = ft_strdup("");
		write(1, MINISHELL, ft_strlen(MINISHELL));
		cap = tgetstr("sc", 0);
		write(1, cap, ft_strlen(cap));
		*cmd_return = 1;
		g_signal = 0;
	}
}

void	ctrl_b(int c)
{
	c = SIGINT;
	return ;
}

void	check_cmd_ret(int *cmd_return)
{
	if (*cmd_return == 3)
		write(1, "Quit: 3\n", ft_strlen("Quit: 3\n"));
	if (g_signal != 1)
	{
		write(1, MINISHELL, ft_strlen(MINISHELL));
		write(1, tgetstr("sc", 0), ft_strlen(tgetstr("sc", 0)));
	}
}
