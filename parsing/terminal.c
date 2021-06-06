/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 08:39:35 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/05 18:54:18 by bamghoug         ###   ########.fr       */
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
		ft_free(tmp);
		write(1, &c, 1);
	}
	return (0);
}

void	init_lines(char **line, char **current)
{
	*line = ft_strdup("");
	*current = NULL;
}

void	init_signals(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_b);
}

void	ctrl_d(struct termios *old)
{
	tcsetattr(STDIN_FILENO, TCSANOW, old);
	write(1, "exit\n", 5);
	exit(0);
}

char	*get_line(t_line **h_line, int *cmd_return)
{
	unsigned char	c;
	char			*line;
	char			*current;
	struct termios	old;

	init_lines(&line, &current);
	check_cmd_ret(cmd_return);
	tcgetattr(STDIN_FILENO, &old);
	init_signals();
	while (1)
	{
		check_signal(&line, cmd_return);
		c = gtc();
		if (c == 4 && ft_strlen(line) == 0)
			ctrl_d(&old);
		if (check_char(h_line, &line, c, &current) == 1)
			break ;
	}
	if (current != NULL)
		ft_free(&current);
	tcsetattr(STDIN_FILENO, TCSANOW, &old);
	return (line);
}
