/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 08:53:29 by bamghoug          #+#    #+#             */
/*   Updated: 2021/03/25 10:46:21 by bamghoug         ###   ########.fr       */
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
    int just_char;

    i = *dquote_ind;
    just_char = -1;
    while (str[0][++i] != '\0')
    {
        if(str[0][i] == '"')
        {
            if(i != 0 && str[0][i - 1] == '\\' && just_char != i - 1)
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
        else if (str[0][i] == '\\')
        {
            if(str[0][i + 1] == '\\')
            {
                rm_char(&str[0], i);
                just_char = i;
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
    int just_char;

    i = -1;
    just_char = -1;
    while(str[0][++i] != '\0')
    {
        if(str[0][i] == '"')
        {
            if (i != 0 && str[0][i - 1] == '\\' && just_char != i - 1)
            {
                rm_char(&str[0], i - 1);
                i -= 1;
            }
            else
                found_dquote(&str[0], &i);
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
        else if (str[0][i] == '\\')
        {
            if(str[0][i + 1] == '\\')
            {
                rm_char(&str[0], i);
                just_char = i;
            }
        }
    }
}

void    clean_replace(t_cmd *s_cmd, t_env **s_env)
{
    int     i;
    t_args  *tmp_args;
    t_files *tmp_file;

    i = -1;
    looking_for_quotes(&s_cmd->cmd, s_env);
    tmp_args = s_cmd->args;
    while (tmp_args)
    {
        looking_for_quotes(&tmp_args->arg, s_env);
        tmp_args = tmp_args->next;
    }
    tmp_file = s_cmd->files;
    while (tmp_file)
    {
        looking_for_quotes(&tmp_file->file, s_env);
        tmp_file = tmp_file->next;
    }
}