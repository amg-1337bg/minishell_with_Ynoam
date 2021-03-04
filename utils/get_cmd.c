/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:21:39 by bamghoug          #+#    #+#             */
/*   Updated: 2021/03/04 19:23:36 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    check_quotes(char c, int *quote, int *dquote)
{
    if(c == 39)
    {
        if(*quote == 0)
            *quote = 1;
        else
            *quote = 0;
    }
    else
    {
        if(*dquote == 0)
            *dquote = 1;
        else
            *dquote = 0;
    }
}

t_cmd   *fill_cmd_struct(char *line, int begin, int end)
{
    t_cmd *ret;

    if((ret = (t_cmd*)malloc(sizeof(t_cmd))) == NULL)
        error();
    ret->cmd = NULL;
    ret->args = NULL;
    ret->operator = NULL;
    ret->full = ft_substr(line, begin, end - begin);
    ret->next = NULL;
    return (ret);
}

t_cmd   *get_full_cmd(char *line, int *i)
{
    int j;
    int quote;
    int dquote;
    t_cmd *ret;

    j = *i;
    quote = 0;
    dquote = 0;
    ret = NULL;
    while (line[j] != '\0')
    {
        if(line[j] == 39 || line[j] == 34)
            check_quotes(line[j], &quote, &dquote);
        else if(line[j] == ';')
        {
            if (quote == 0 && dquote == 0)
                break;
        }
        j++;
    }
    ret = fill_cmd_struct(line, *i, j);
    *i = j;
    return (ret);
}


void    get_cmd(t_cmd **s_cmd, char *line)
{
    t_cmd   *tmp;
    t_cmd   *last;
    int     i;
    
    i = 0;
    while (line[i] != '\0')
    {
        tmp = get_full_cmd(line, &i);
        if((last = ft_lstcmd(*s_cmd)) == NULL)
            *s_cmd = tmp;
        else
            last->next = tmp;
        if (line[i] == ';')
            i++;
    }
    
}