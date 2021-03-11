/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 08:53:29 by bamghoug          #+#    #+#             */
/*   Updated: 2021/03/10 16:20:17 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    quote_dquotes(t_args *arg, int *i, char c)
{
    char    *new_arg;
    char    *tmp;
    int     j;

    j = *i;
    new_arg = NULL;
    while (arg->arg[++j] != '\0')
    {
        if(j != 0 && arg->arg[j] == c && arg->arg[j - 1] != '\\')
            break;
    }
    if((*i) != 0 && arg->arg[*i - 1] == 92)
    {
        if(arg->arg[j - 1] == 92)
        {
            new_arg = ft_substr(arg->arg, *i, (j - 1) - *i);
            tmp = new_arg;
            new_arg = ft_strjoin(new_arg, &c);
            free(tmp);
            // printf ("new arg = %s\n", new_arg);
        }
        else
        {
            printf("No multiline commands\n");
            return ;
        }
    }
    else
        new_arg = ft_substr(arg->arg, *i + 1, j - (*i + 1));
    tmp = new_arg;
    new_arg = ft_strjoin(new_arg, ft_strdup(&arg->arg[j + 1]));
    free(tmp);
    tmp = arg->arg;
    arg->arg = new_arg;
    free(tmp);
    *i = j;
}

void    clean_arg(t_cmd *s_cmd)
{
    int     i;
    t_args  *tmp_arg;

    tmp_arg = s_cmd->args;
    i = -1;
    while (tmp_arg)
    {
        while (tmp_arg->arg[++i] != '\0')
        {
            if(tmp_arg->arg[i] == '"')
                quote_dquotes(tmp_arg, &i, '"');
            else if(tmp_arg->arg[i] == '\'')
                quote_dquotes(tmp_arg, &i, '\'');
        }
        tmp_arg = tmp_arg->next;
    }
}