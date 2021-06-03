/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 08:53:29 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/02 18:24:25 by bamghoug         ###   ########.fr       */
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
                looking_for_dollar(str, s_env, dquote_ind, &i);
                *dquote_ind = i - 2;
                return (0);
            }
        }
        else if (str[0][i] == '\\' && str[0][i + 1] == '\\')
        {
            rm_char(str, i);
            just_char = i;
        }
    }
    return (0);
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

void    looking_for_dollar(char **str, t_env *s_env, int *from, int *to)
{
    int diff;
    
    while (*from < *to && str[0][*from] != '\0')
    {
        if (str[0][*from] == '$')
        {
            diff = *from;
            dollar_founded(str, s_env, from, -2);
            // *to += from - diff;
        }
        *from++;
    }
}

char    *insert_var_value(char *after, char *value, char *before)
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
    tmp = value;
    value = ft_strtrim(value, " ");
    free(tmp);
    tmp = str[0];
    str[0] = insert_var_value(ft_substr(str[0], 0, *i), value, ft_strdup(&str[0][begin]));
    free(tmp);
    if (ft_strlen(value) != 0)
    {    
        (*i) += (ft_strlen(value));
        if ((*i) < 0)
            (*i) *= -1;
    }
    (*i) -= 1;
    free(key);
    free(value);
}

int     quotes_function(char **str, t_env *s_env, int *i, int just_char)
{
    if ((*i) != 0 && str[0][(*i) - 1] == '\\' && just_char != (*i) - 1)
    {
        rm_char(str, (*i) - 1);
        (*i) -= 1;
    }
    else
    {
        if(str[0][(*i)] == '"')
        {
            if (found_dquote(str, s_env, i) == -1)
                return (-1);
        }
        else
        {
            if (found_quote(str, i) == -1)
                return (-1);
        }
    }
    return (0);
}

void    char_remove(char **str, int *i, int *just_char)
{
    if (str[0][*i] == '\\')
    {
        rm_char(str, (*i));
        (*just_char) = (*i);
    }
    else
    {
        rm_char(str, (*i) - 1);
        (*i) -= 1;
    }
}

int     special_chars(char **str, t_env **s_env, int cmd_return)
{
    int i;
    int just_char;
    char *tmp;

    i = -1;
    just_char = -1;
    while(*str != NULL && str[0][++i] != '\0')
    {
        if(str[0][i] == '"' || str[0][i] == '\'')
            quotes_function(str, s_env, &i, just_char);
        else if (str[0][i] == '|' && i > 0 && str[0][i - 1] == '\\' && just_char != i - 1)
            char_remove(str, &i, &just_char);
        else if (str[0][i] == ';' && i > 0 && str[0][i - 1] == '\\' && just_char != i - 1)
            char_remove(str, &i, &just_char);
        else if ((str[0][i] == '>' || str[0][i] == '<') && i > 0 && str[0][i - 1] == '\\' && just_char != i - 1)
            char_remove(str, &i, &just_char);
        else if (str[0][i] == '\\' && str[0][i + 1] == '\\')
            char_remove(str, &i, &just_char);
        else if (str[0][i] == ' ' && i > 0 && str[0][i - 1] == '\\' && just_char != i - 1)
            char_remove(str, &i, &just_char);
        else if (str[0][i] == '$')
        {
            if (str[0][i + 1] == '?')
            {
                tmp = str[0];
                str[0] = insert_var_value(ft_substr(str[0], 0, i), ft_itoa(cmd_return), ft_strdup(&str[0][i + 2]));
                free(tmp);
            }
            else
                dollar_founded(str, s_env, &i, just_char);
        }
    }
    return (0);
}

t_args    *arg_to_head(t_args *arg, char *cmd, int from, int *i)
{
    t_args  *args;
    t_args  *tmp;
    char    *str;
    
    str = ft_substr(cmd, from, (*i) - from);
    if((args = (t_args*)malloc(sizeof(t_args))) == NULL)
        error();
    args->arg = str;
    args->next = NULL;
    tmp = ft_lastarg(arg);
    if (tmp == NULL)
    {
        *i += space_count(&cmd[*i]) - 1;        
        return (args);
    }
    else
        tmp->next = args;
    (*i) += space_count(&cmd[*i]) - 1;
    return (arg);
}

void    look_for_args(t_cmd *cmd, char *tmp, int i)
{
    int from;
    t_args *arg;
    t_args *tmp_arg;

    from = -1;
    arg = NULL;
    i += space_count(&tmp[i]) - 1;
    while (tmp[++i] != '\0')
    {
        if (from == -1)
            from = i;
        if (tmp[i] == ' ')
        {
            arg = arg_to_head(arg, tmp, from, &i);
            from = -1;
        }
    }
    if (from != -1)
        arg = arg_to_head(arg, tmp, from, &i);
    tmp_arg = ft_lastarg(arg);
    if (tmp != NULL)
    {
        tmp_arg->next = cmd->args;
        cmd->args = arg;
    }
}

void    check_again(t_cmd *cmd)
{
    int i;
    int from;
    char *tmp;

    i = -1;
    from = -1;
    tmp = NULL;
    while (cmd->cmd[++i] != '\0')
    {
        if (cmd->cmd[i] == ' ')
        {
            tmp = cmd->cmd;
            cmd->cmd = ft_substr(cmd->cmd, 0, i);
            look_for_args(cmd, tmp, i);
            free(tmp);
            return;
        }
    }
}

int     clean_replace(t_cmd *s_cmd, t_env *s_env, int cmd_return)
{
    char    *tmp;
    t_args  *tmp_args;
    t_files *tmp_file;
    t_cmd   *tmp_pipe;
    int     i;

    i = 0;
    if (special_chars(&s_cmd->cmd, s_env, cmd_return) != 0)
        return (-1);
    tmp_args = s_cmd->args;
    while (tmp_args)
    {
        printf("arg = %s\n", tmp_args->arg);
        if(special_chars(&tmp_args->arg, s_env, cmd_return) != 0)
            return (-1);
        printf("arg = %s\n", tmp_args->arg);
        tmp_args = tmp_args->next;
    }
    check_again(s_cmd);
    tmp_file = s_cmd->files;
    while (tmp_file)
    {
        if (tmp_file->file[0] == '$')
        {
            tmp = ft_strdup(tmp_file->file); 
            dollar_founded(&tmp_file->file, s_env, &i, 0);
            if (strlen(tmp_file->file) == 0)
                tmp_file->file = tmp;
            else
                free (tmp);
        }
        else
            if (special_chars(&tmp_file->file, s_env, cmd_return) != -1)
                return (-1);
        tmp_file = tmp_file->next;
    }
    tmp_pipe = s_cmd->pipe;
    if (tmp_pipe != NULL)
    {
        if (special_chars(&tmp_pipe->cmd, s_env, cmd_return) != 0)
            return (-1);
        tmp_args = tmp_pipe->args;
        while (tmp_args)
        {
            if(special_chars(&tmp_args->arg, s_env, cmd_return) != 0)
                return (-1);
            tmp_args = tmp_args->next;
        }
        tmp_file = tmp_pipe->files;
        while (tmp_file)
        {
            if (special_chars(&tmp_file->file, s_env, cmd_return) != -1)
                return (-1);
            tmp_file = tmp_file->next;
        }    
    }
    return (0);
}