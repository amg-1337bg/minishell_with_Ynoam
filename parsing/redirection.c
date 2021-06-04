/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:41:34 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/03 19:23:47 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     get_redirection(t_cmd *s_cmd, int *i, int from, int just_char)
{
    t_files *fill;
    t_files *tmp;

    if(*i == 0 || s_cmd->full[*i - 1] != '\\' || (s_cmd->full[*i - 1] == '\\' && just_char == *i - 1))
    {
        if (from != (*i))
        {
            get_cmd_args(s_cmd, from, i);
            (*i)++;
        }
        fill = (t_files*)malloc(sizeof(t_files));
        fill->type = get_redir_type(s_cmd, i);
        fill->file = get_filename(s_cmd, i, just_char);
        fill->dollar = 0;
        fill->next = NULL;
        if((tmp = ft_lastfile(s_cmd->files)) == NULL)
            s_cmd->files = fill;
        else
            tmp->next = fill;
        (*i) += space_count(&s_cmd->full[*i]) - 1;
        return (1);
    }
    return (0);
}

char    *get_redir_type(t_cmd *s_cmd, int *i)
{
    char    c;
    char    *res;

    c = s_cmd->full[(*i)];
    if (c == '<')
    {
        (*i)++;
        return (ft_strdup("<"));
    }
    else
    {
        if (s_cmd->full[(*i) + 1] == '>')
        {
            (*i) += 2;
            return (ft_strdup(">>"));
        }
        else
        {
            (*i)++;   
            return (ft_strdup(">"));
        }
    }    
}

char    *get_filename(t_cmd *s_cmd, int *i, int just_char)
{
    char    *ret;
    int     from;
    
    (*i) += space_count(&s_cmd->full[(*i)]);
    from = *i;
    while (s_cmd->full[*i] != '\0')
    {
        if(s_cmd->full[*i] == 39 || s_cmd->full[*i] == 34)
            quote_detected(s_cmd->full, i, just_char);
        else if(s_cmd->full[*i] == '\\' && s_cmd->full[*i + 1] == '\\')
            just_char = *i + 1;
        else if (s_cmd->full[*i] == '>' || s_cmd->full[*i] == '<')
        {
            if (s_cmd->full[*i - 1] == '\\' && just_char == *i - 1)
                break ;
            else if (s_cmd->full[*i - 1] != '\\')
                break ;    
        }
        else if (s_cmd->full[*i] == ' ' && (s_cmd->full[(*i) - 1] != '\\' || just_char == (*i) - 1))
            break ;
        else if (s_cmd->full[(*i)] == '|' && (s_cmd->full[(*i) - 1] != '\\' || just_char == (*i) - 1))
            break ;
        (*i)++;
    }
    ret = ft_substr(s_cmd->full, from, *i - from);
    return (ret);
}