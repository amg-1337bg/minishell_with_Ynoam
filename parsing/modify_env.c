/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:37:13 by bamghoug          #+#    #+#             */
/*   Updated: 2021/03/05 15:05:52 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    crt_env(t_env *s_env, char *key, char *value)
{
    t_env *fill;
    t_env *tmp;

    if ((fill = (t_env*)malloc(sizeof(t_env))) == NULL)
        error();
    fill->key = key;
    fill->value = value;
    fill->next = NULL;
    if ((tmp = ft_lstlst(s_env)) == NULL)
        s_env = fill;
    else
        tmp->next = fill;
}

void    mdf_env(t_env *s_env, char *key, char *value)
{
    t_env *tmp;
    int found;

    tmp = s_env;
    found = 0;
    while (tmp)
    {
        if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
        {
            free(tmp->value);
            tmp->value = value;
            found = 1;
            break ;
        }
        tmp = tmp->next;
    }
    if (found != 1)
        crt_env(s_env, key, value);
}

void    dlt_env(t_env *s_env, char *key)
{
    t_env *first;
    t_env *second;

    first = s_env;
    while(first)
    {
        second = first->next;
        if(second != NULL)
        {
            if((ft_strncmp(second->key, key, ft_strlen(key))) == 0)
            {
                first->next = second->next;
                free(second->key);
                free(second->key);
                free(second);
                return ;
            }
        }
        else
        {
            if((ft_strncmp(first->key, key, ft_strlen(key))) == 0)
            {
                free(first->key);
                free(first->value);
                s_env = first->next;
                free(first);
                return ;
            }
        }
        first = first->next;
    }
}

char    *search_env(t_env *s_env, char *key)
{
    t_env *tmp;

    tmp = s_env;
    while(tmp)
    {
        if (ft_strncmp(tmp->key, key, ft_strlen(tmp->key)) == 0)
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}