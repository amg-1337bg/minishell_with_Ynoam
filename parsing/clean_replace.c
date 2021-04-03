/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 08:53:29 by bamghoug          #+#    #+#             */
/*   Updated: 2021/04/03 10:13:51 by ynoam            ###   ########.fr       */
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

int    found_dquote(char **str, t_env *s_env, int *dquote_ind)
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
            }
            else
            {
                rm_char(str, i);
                rm_char(str, *dquote_ind);
                looking_for_dollar(str, s_env, *dquote_ind, &i);
                *dquote_ind = i - 2;
                return (0);
            }
        }
        else if (str[0][i] == '\\' && str[0][i + 1] == '\\')
        {
            rm_char(&str[0], i);
            just_char = i;
        }
    }
    return (-1);
}

int    found_quote(char **str, int *quote_ind)
{
    int i;

    i = *quote_ind;
    while (str[0][++i] != '\0')
    {
        if(str[0][i] == '\'')
        {
            rm_char(str, i);
            rm_char(str, *quote_ind);
            *quote_ind = i - 2;
            return (0);
        }
    }
    return (-1);
}

void    looking_for_dollar(char **str, t_env *s_env, int from, int *to)
{
    int diff;
    
    while (from < to && str[0][from] != '\0')
    {
        if (str[0][from] == '$')
        {
            diff = from;
            dollar_founded(str, s_env, &from, -2);
            *to += from - diff;
        }
        from++;
    }
}

char    *insert_var_value(char *after, char *value, char *before, int *i)
{
    char    *ret;
    char    *tmp;

    tmp = ft_strjoin(after, value);
    ret = ft_strjoin(tmp, before);
    free(tmp);
    free(after);
    free(before);
    return (ret);
}

void    dollar_founded(char **str, t_env *s_env, int *i, int just_char)
{
    int     begin;
    char    *value;
    char    *key;
    char    *tmp;

    begin = *i;
    if(begin != 0 && str[0][begin - 1] == '\\' && (just_char != -2 && just_char != begin - 1))
    {
        rm_char(str, begin - 1);
        *i -= 1;
        return;
    }
    while (str[0][++begin] != '\0')
    {
        if(ft_isalnum(str[0][begin]) != 1 && str[0][begin] != '_')
            break ;
    }
    key = ft_substr(str[0], (*i) + 1, begin - ((*i) + 1));
    if (ft_strlen(key) == 0)
    {
        free(key);
        return ;
    }
    value = ft_strdup(search_env(s_env, key));
    tmp = str[0];
    str[0] = insert_var_value(ft_substr(str[0], 0, *i), value, ft_strdup(&str[0][begin]), i);
    free(tmp);
    *i += ft_strlen(value) - 1;
}

int    looking_for_quotes(char **str, t_env **s_env)
{
    int i;
    int just_char;

    i = -1;
    just_char = -1;
    while(str[0] != NULL && str[0][++i] != '\0')
    {
        if(str[0][i] == '"')
        {
            if (i != 0 && str[0][i - 1] == '\\' && just_char != i - 1)
            {
                rm_char(&str[0], i - 1);
                i -= 1;
            }
            else
            {
                if (found_dquote(&str[0], s_env, &i) == -1)
                    return (-1);
            }
        }
        else if(str[0][i] == '\'')
        {
            if (i != 0 && str[0][i - 1] == '\\' && just_char != i - 1)
            {
                rm_char(&str[0], i - 1);
                i -= 1;
            }
            else
            {
                if (found_quote(&str[0], &i) == -1)
                    return (-1);
                just_char = i;
            }
        }
        else if (str[0][i] == '|' && str[0][i - 1] == '\\' && just_char == i - 1)
        {
            rm_char(str, i - 1);
            i -= 1;
        }
        else if (str[0][i] == '\\' && str[0][i + 1] == '\\')
        {
            rm_char(&str[0], i);
            just_char = i;
        }
        else if (str[0][i] == '$')
            dollar_founded(str, s_env, &i, just_char);
            
    }
    return (0);
}

int    clean_replace(t_cmd *s_cmd, t_env *s_env)
{
    int     i;
    t_args  *tmp_args;
    t_files *tmp_file;
    t_cmd   *tmp_pipe;

    i = -1;
    if (looking_for_quotes(&s_cmd->cmd, s_env) != 0)
        return (-1);
    tmp_args = s_cmd->args;
    while (tmp_args)
    {
        if(looking_for_quotes(&tmp_args->arg, s_env) != 0)
            return (-1);
        tmp_args = tmp_args->next;
    }
    tmp_file = s_cmd->files;
    while (tmp_file)
    {
        if (looking_for_quotes(&tmp_file->file, s_env) != -1)
            return (-1);
        tmp_file = tmp_file->next;
    }
    tmp_pipe = s_cmd->pipe;
    if (tmp_pipe != NULL)
    {
        if (looking_for_quotes(&tmp_pipe->cmd, s_env) != 0)
            return (-1);
        tmp_args = tmp_pipe->args;
        while (tmp_args)
        {
            if(looking_for_quotes(&tmp_args->arg, s_env) != 0)
                return (-1);
            tmp_args = tmp_args->next;
        }
        tmp_file = tmp_pipe->files;
        while (tmp_file)
        {
            if (looking_for_quotes(&tmp_file->file, s_env) != -1)
                return (-1);
            tmp_file = tmp_file->next;
        }    
    }
    return (0);
}