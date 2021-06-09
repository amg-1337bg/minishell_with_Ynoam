/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 21:27:34 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/07 15:40:18 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	gtc(void)
{
	char			c;
	char			seq;
	struct termios	tee;

	c = 0;
	seq = 0;
	tcgetattr(STDIN_FILENO, &tee);
	tee.c_lflag &= ~(ICANON | ECHO);
	tee.c_cc[VMIN] = 0;
	tee.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &tee);
	read(STDIN_FILENO, &c, 1);
	if (c == 27)
	{
		read(STDIN_FILENO, &seq, 1);
		if (seq > 0)
			c += seq;
		read(STDIN_FILENO, &seq, 1);
		if (seq > 0)
			c += seq;
	}
	return (c);
}

char	*char_join(char *str, char c)
{
	char	*ret;
	int		len;
	int		i;

	len = ft_strlen(str);
	ret = malloc((len + 2) * sizeof(char));
	i = -1;
	while (str[++i] != '\0')
		ret[i] = str[i];
	ret[i++] = c;
	ret[i] = '\0';
	return (ret);
}

void	del_write(char *line)
{
	char	*cap;

	cap = tgetstr("rc", 0);
	write(1, cap, ft_strlen(cap));
	cap = tgetstr("cd", 0);
	write(1, cap, ft_strlen(cap));
	write(1, tgetstr("sc", 0), ft_strlen(tgetstr("sc", 0)));
	write(1, line, ft_strlen(line));
}

void	del_char(char **line)
{
	char	*del;
	int		len;

	len = ft_strlen(line[0]);
	if (len != 0)
	{
		del = tgetstr("le", NULL);
		write(1, del, ft_strlen((del)));
		del = tgetstr("dc", NULL);
		write(1, del, ft_strlen((del)));
		rm_char(line, len - 1);
	}
}
