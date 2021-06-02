/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 08:39:35 by bamghoug          #+#    #+#             */
/*   Updated: 2021/05/30 20:44:22 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	modify_attr()
{
	struct termios tee;
    
	tcgetattr(STDIN_FILENO, &tee);
    tee.c_lflag &= ~(ICANON);
	tee.c_lflag &= ~(ECHO);
	tee.c_cc[VMIN] = 0;
    tee.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &tee);
}

unsigned char   gtc()
{
    unsigned char c;
    unsigned char seq;
    struct termios tee;
    struct termios old;
    
    c = 0;
    seq = 0;
    tcgetattr(STDIN_FILENO, &tee);
    old = tee;
    tee.c_lflag &= ~(ICANON);
	tee.c_lflag &= ~(ECHO);
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
	tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return c;
}

void	del_write(char *line)
{
	char *cap;

    cap = tgetstr("rc", 0);
    write(1, cap, ft_strlen(cap));
    cap = tgetstr("cd", 0);
	write(1, cap, ft_strlen(cap));
	write(1, line, ft_strlen(line));
}

t_line	*last_line(t_line *head)
{
	t_line *tmp;

	tmp = head;
	if(head == NULL)
		return NULL;
	while (tmp)
	{
		if(tmp->next == NULL)
			break;
		tmp = tmp->next;
	}
	return tmp;
}

void	add_to_history(t_line **h_line ,char *line)
{
	t_line *fill;
	t_line *tmp;

	fill = malloc(sizeof(t_line));
	fill->line = ft_strdup(line);
	fill->next = NULL;
	fill->prev = NULL;
	if((tmp = last_line(h_line[0])) == NULL)
		h_line[0] = fill;
	else
	{
		tmp->next = fill;
		fill->prev = tmp;
	}
}

void	del_char(char **line)
{
	char    *del;
    int     len;

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

void    handle_up(t_line **h_line, char **line)
{
    char    *tmp;
    
    tmp = h_line[1]->line;
    line[0] = ft_strdup(h_line[1]->line);
    h_line[2] = h_line[1];
    h_line[1] = h_line[1]->prev;
    del_write(tmp);
}

void    handle_down(t_line **h_line, char **line)
{
    if(h_line[2])
    {
        if(h_line[2]->next == NULL)
        {
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
}

void    handle_nl(t_line **h_line, char **line)
{
    if (ft_strlen(line[0]) != 0)
    {
        add_to_history(&h_line[0], line[0]);
        h_line[1] = last_line(h_line[0]);
        h_line[2] = NULL;
    }
}

int    check_char(t_line **h_line, char **line, unsigned char c)
{
    if (c == (unsigned char)183 && h_line[1]) // up key
    // {
    //     del_write(h_line[1]->line);
    //     line[0] = ft_strdup(h_line[1]->line);
    //     h_line[2] = h_line[1];
    //     h_line[1] = h_line[1]->prev;
    // }
        handle_up(h_line, line);
    else if (c == (unsigned char)184 && h_line[2]) // down key
    // {
    //     if(h_line[2]->next == NULL)
    //     {
    //         del_write(line[0]);
    //         h_line[1] = h_line[2];
    //         h_line[2] = NULL;
    //     }
    //     else
    //     {
    //         h_line[1] = h_line[2];
    //         h_line[2] = h_line[2]->next;
    //         del_write(h_line[2]->line);
    //         line[0] = ft_strdup(h_line[2]->line);
    //     }
    // }
        handle_down(h_line, line);
    else if (c == (unsigned char)127) // backspace
        del_char(line);
    else if (c == (unsigned char)10)
    {
        handle_nl(h_line, line);
        write(1, "\n", 1);
        return (1);
    }
    else if (c >= (unsigned char)32 && c <= (unsigned char)126)
    {
    	*line = ft_strjoin(*line, (char*)&c);
    	write(1, &c, 1);
    }
    return (0);
}

char    *get_line(t_line **h_line)
{
    unsigned char    c;
    int     flag;
    char    *line;

    flag = 0;
    line = ft_strdup("");
    signal(SIGINT, ctrl_c);
    signal(SIGQUIT, ctrl_c);
    while (1)
    {
        if (flag == 0)
        {
            write(1, Minishell, ft_strlen(Minishell));
            write(1, tgetstr("sc", 0), ft_strlen(tgetstr("sc", 0)));
            flag = 1;
        }
        c = gtc();
        if (check_char(h_line, &line, c) == 1)
            break ;
    }
    return (line);
}