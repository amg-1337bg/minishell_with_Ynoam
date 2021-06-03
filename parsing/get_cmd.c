/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 12:21:39 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/02 14:48:03 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    check_quotes(char c, int *quote, int *dquote)
{
    if (c == 39)
    {
        if (*quote == 0)
            *quote = 1;
        else
            *quote = 0;
    }
    else
    {
        if (*dquote == 0)
            *dquote = 1;
        else
            *dquote = 0;
    }
}

int     quote_traitement(char *line, int *j, char c)
{
    while (line[++(*j)] != '\0')
    {
        if (line[*j] == c)
            return (1);
    }
    return (0);
}

int     dquote_traitement(char *line, int *j, char c, int just_char)
{
    while (line[++(*j)] != '\0')
    {
        if (line[(*j)] == '\\' && line[(*j) + 1] == '\\')
            just_char = (*j) + 1;
        else if (line[*j] == '"')
        {
            if (line[(*j) - 1] == '\\' && just_char == (*j) - 1)
                return (1);
            else if (line[(*j) - 1] != '\\')
                return (1);
        }
    }
    return (0);
}

int     quote_detected(char *line, int *j, int just_char)
{
    char c;

    c = line[*j];
    if (*j == 0 || line[*j - 1] != '\\' || (line[*j - 1] == '\\' && just_char == *j - 1))
    {
        if(c == '\'')
        {
            if (quote_traitement(line, j, c) == 1)
                return (1);
        }
        else
        {
            if (dquote_traitement(line, j, c, just_char) == 1)
                return (1);
        }
    }
    printf("ERROR: No Multiline Commands\n");
    return (0);
}

t_cmd   *fill_cmd_struct(char *line, int begin, int end)
{
    t_cmd   *ret;
    char    *str;
    char    *tmp;

    str = ft_substr(line, begin, end - begin);
    tmp = str;
    str = ft_strtrim(str, " ");
    free(tmp);
    if (ft_strlen(str) == 0)
    {
        printed_errors(Syntax_error);
        return (NULL);
    }
    if((ret = (t_cmd*)malloc(sizeof(t_cmd))) == NULL)
        error();
    ret->cmd = NULL;
    ret->args = NULL;
    ret->files = NULL;
    ret->full = str;
    ret->pipe = NULL;
    ret->next = NULL;
    return (ret);
}

t_cmd   *get_full_cmd(char *line, int *i)
{
    int j;
    int just_char;
    t_cmd *ret;

    j = *i;
    ret = NULL;
    just_char = -1;
    while (line[j] != '\0')
    {
        if(line[j] == 39 || line[j] == 34)
        {
            if (quote_detected(line, &j, just_char) == 0)
                return (0);
        }
        else if(line[j] == ';')
        {
            if (j == 0)
            {
                printed_errors(Syntax_error);
                return (0);
            }
            if (line[j - 1] != '\\' || just_char == j - 1)
                break ;
        }
        else if(line[j] == '\\' && line[j + 1] == '\\')
            just_char = j + 1;
        j++;
    }
    ret = fill_cmd_struct(line, *i, j);
    *i = j;
    return (ret);
}

int    get_cmd(t_cmd **s_cmd, t_env *s_env, char *line, int *ret)
{
    t_cmd   *tmp;
    t_cmd   *last;
    int     i;
    
    i = 0;
    line = ft_strtrim(line, " ");
    while (line[i] != '\0')
    {
        tmp = get_full_cmd(line, &i);
        if(tmp == NULL)
        {
            *ret = 258;
            return (-1);
        }
        if((last = ft_lstcmd(s_cmd[0])) == NULL)
            s_cmd[0] = tmp;
        else
            last->next = tmp;
        if (line[i] == ';')
            i++;
    }
    if (cmd_parser(s_cmd, s_env) != 0)
        return(-1);
    return (0);
}