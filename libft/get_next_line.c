/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 15:18:39 by ynoam             #+#    #+#             */
/*   Updated: 2021/03/27 12:50:586ynobamghoug      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (1);
}

int	g_next_line(char **stk, char *t, ssize_t r, char **line)
{
	free(t);
	if (!(*line) && ft_free(stk))
		return (-1);
	*stk = ft_from_newline(*stk);
	if (!(*stk) && r != 0 && ft_free(stk))
		return (-1);
	if (r == 0 && ft_free(stk))
		return (0);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	ssize_t		r;
	char		*t;
	static char	*stk[4864];

	r = 1;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	t = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!t)
		return (-1);
	while (ft_search(stk[fd]))
	{
		r = read(fd, t, BUFFER_SIZE);
		if (r == 0)
			break ;
		if (r == -1 && ft_free(&t) && ft_free(&stk[fd]))
			return (-1);
		t[r] = '\0';
		stk[fd] = ft_join(stk[fd], t);
		if (!(stk[fd]) && ft_free(&t))
			return (-1);
	}
	*line = ft_sub(stk[fd], 0);
	return (g_next_line(&(stk[fd]), t, r, line));
}
