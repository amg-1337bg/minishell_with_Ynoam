/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 08:53:29 by bamghoug          #+#    #+#             */
/*   Updated: 2021/03/16 16:18:32 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    rm_char(char **str, int char_index)
{
    char    *tmp;
    char    *tmp1;
    char    *tmp3;

    tmp = *str;
    if(char_index == 0)
        *str = ft_strdup(&tmp[char_index + 1]);
    else
    {
        *str = ft_substr(*str, 0, char_index);
        tmp1 = *str;
        tmp3 = ft_strdup(&tmp[char_index + 1]);
        *str = ft_strjoin(*str, tmp3);
        free(tmp1);
        free(tmp3);
    }
    free(tmp);
}

void    found_dquote(char **str, int *dquote_ind)
{
    int i;

    i = *dquote_ind;
    while (str[0][++i] != '\0')
    {
        if(str[0][i] == '"')
        {
            if(i != 0 && str[0][i - 1] == '\\')
            {
                rm_char(str, i - 1);
                i -= 1;
                *dquote_ind -= 2;
            }
            else
            {
                rm_char(str, i);
                rm_char(str, *dquote_ind);
                *dquote_ind -= 3;
                return ;
            }
        }
    }
}

void    found_quote(char **str, int *quote_ind)
{
    int i;

    i = *quote_ind;
    while (str[0][++i] != '\0')
    {
        if(str[0][i] == '\'')
        {
            if(i != 0 && str[0][i - 1] == '\\')
            {
                rm_char(str, i - 1);
                i -= 1;
                *quote_ind -= 1;
            }
            else
            {
                rm_char(str, i);
                rm_char(str, *quote_ind);
                *quote_ind -= 2;
                return ;
            }
        }
    }
}

void    looking_for_quotes(char **str, t_env **s_env)
{
    int i;

    i = -1;
    while(str[0][++i] != '\0')
    {
        if(str[0][i] == '"')
        {
            if (i != 0 && str[0][i - 1] == '\\')
            {
                rm_char(&str[0], i - 1);
                i -= 1;
            }
            else
                found_dquote(&str[0], &i);
            printf("%s\n", &str[0][i]);
        }
        else if(str[0][i] == '\'')
        {
            if (i != 0 && str[0][i - 1] == '\\')
            {
                rm_char(str[0], i - 1);
                i -= 1;
            }
            else
                found_quote(&str[0], &i);
        }
    }
}

void    clean_replace(t_cmd *s_cmd, t_env **s_env)
{
    int     i;
    t_args  *tmp;

    i = -1;
    looking_for_quotes(&s_cmd->cmd, s_env);
    tmp = s_cmd->args;
    while (tmp)
    {
        looking_for_quotes(&tmp->arg, s_env);
        tmp = tmp->next;
    }
}