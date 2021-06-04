/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 08:39:35 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/04 11:12:54 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_char(t_line **h_line, char **line, unsigned char c, char **current)
{
	char	*tmp;
	if (c == (unsigned char)183 && h_line[1])
		handle_up(h_line, line, current);
	else if (c == (unsigned char)184 && h_line[2])
		handle_down(h_line, line, current);
	else if (c == (unsigned char)127)
		del_char(line);
	else if (c == (unsigned char)10)
	{
		handle_nl(h_line, line);
		write(1, "\n", 1);
		return (1);
	}
	else if (c >= (unsigned char)32 && c <= (unsigned char)126)
	{
		tmp = *line;
		*line = char_join(*line, c);
		write(1, &c, 1);
	}
	return (0);
}

char	*get_line(t_line **h_line, int *cmd_return)
{
	unsigned char	c;
	char			*line;
	char			*current;
	struct termios	old;

	line = ft_strdup("");
	current = ft_strdup("");
	check_cmd_ret(cmd_return);
	tcgetattr(STDIN_FILENO, &old);
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_b);
	while (1)
	{
		check_signal(&line, cmd_return);
		c = gtc();
		if (c == 4 && ft_strlen(line) == 0)
		{
			tcsetattr(STDIN_FILENO, TCSANOW, &old);
			write(1, "exit\n", 5);
			exit(0);
		}
		if (check_char(h_line, &line, c, &current) == 1)
			break ;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &old);
	return (line);
}
