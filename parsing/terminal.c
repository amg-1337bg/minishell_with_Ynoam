/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 08:39:35 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/01 19:32:32 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char   gtc()
{
    unsigned char c;
    unsigned char seq;
    struct termios tee;

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
    return c;
}

char *char_join(char *str, char c)
{
    char *ret;
    int len;
    int i;

    len = ft_strlen(str);
    ret = malloc((len + 2) * sizeof(char));
    i= -1;
    while (str[++i] != '\0')
        ret[i] = str[i];
    ret[i++] = c;
    ret[i] = '\0';
    return (ret);
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

void    handle_up(t_line **h_line, char **line, char **current)
{
    if (h_line[2] == NULL)
        *current = ft_strdup(*line);
    del_write(h_line[1]->line);
    line[0] = ft_strdup(h_line[1]->line);
    h_line[2] = h_line[1];
    h_line[1] = h_line[1]->prev;
}

void    handle_down(t_line **h_line, char **line, char **current)
{
    if(h_line[2]->next == NULL)
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

void    handle_nl(t_line **h_line, char **line)
{
    if (ft_strlen(line[0]) != 0)
    {
        add_to_history(&h_line[0], line[0]);
        h_line[1] = last_line(h_line[0]);
        h_line[2] = NULL;
    }
}

int    check_char(t_line **h_line, char **line, unsigned char c, char **current)
{   
    if (c == (unsigned char)183 && h_line[1]) // up key
        handle_up(h_line, line , current);
    else if (c == (unsigned char)184 && h_line[2]) // down key
        handle_down(h_line, line, current);
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
        *line = char_join(*line, c);
    	write(1, &c, 1);
    }
    return (0);
}
void    ctrl_b(int c)
{
    return;
}
char    *get_line(t_line **h_line, struct termios old, int *cmd_return)
{
    unsigned char    c;
    char    *line;
    char    *current;

    line = ft_strdup("");
    current = ft_strdup("");
    if (*cmd_return == 3)
        write(1, "Quit: 3\n", ft_strlen("Quit: 3\n"));
    if (*cmd_return != 2)
    {
        write(1, Minishell, ft_strlen(Minishell));
        write(1, tgetstr("sc", 0), ft_strlen(tgetstr("sc", 0)));
    }
    signal(SIGINT, ctrl_c);
    signal(SIGQUIT, ctrl_b);
    while (1)
    {
        if (g_signal == 1)
        {
            free(line);
            line = ft_strdup("");
            *cmd_return = 1;
            g_signal = 0;
        }
        c = gtc();
        if (c == 4 && ft_strlen(line) == 0)
        {
            write(1, "exit\n", 5);
            exit(0);
        }
        if (check_char(h_line, &line, c, &current) == 1)
            break ;
    }
    return (line);
}