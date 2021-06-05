/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 21:29:32 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/03 21:39:11 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_up(t_line **h_line, char **line, char **current)
{
	if (h_line[2] == NULL)
		*current = ft_strdup(*line);
	del_write(h_line[1]->line);
	free(*line);
	line[0] = ft_strdup(h_line[1]->line);
	h_line[2] = h_line[1];
	h_line[1] = h_line[1]->prev;
}

void	handle_down(t_line **h_line, char **line, char **current)
{
	if (h_line[2]->next == NULL)
	{
		*line = *current;
		del_write(line[0]);
		h_line[1] = h_line[2];
		h_line[2] = NULL;
	}
	else
	{
		h_line[1] = h_line[2];
		h_line[2] = h_line[2]->next;
		del_write(h_line[2]->line);
		line[0] = ft_strdup(h_line[2]->line);
	}
}

void	handle_nl(t_line **h_line, char **line)
{
	if (ft_strlen(line[0]) != 0)
	{
		add_to_history(&h_line[0], line[0]);
		h_line[1] = last_line(h_line[0]);
		h_line[2] = NULL;
	}
}

void	add_to_history(t_line **h_line, char *line)
{
	t_line	*fill;
	t_line	*tmp;

	fill = malloc(sizeof(t_line));
	fill->line = ft_strdup(line);
	fill->next = NULL;
	fill->prev = NULL;
	tmp = last_line(h_line[0]);
	if (tmp == NULL)
		h_line[0] = fill;
	else
	{
		tmp->next = fill;
		fill->prev = tmp;
	}
}
