/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:31:59 by bamghoug          #+#    #+#             */
/*   Updated: 2021/03/05 11:53:53 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    convert_env_to_cmd(t_cmd *s_cmd, t_env **s_env)
{
    char    *tmp;
    char    *value;
    
    tmp = s_cmd->cmd;
    value = search_env(*s_env, &s_cmd->cmd[1]);
    s_cmd->cmd = value;
    free(tmp);
}

void    get_the_cmd(t_cmd *s_cmd, t_env **s_env)
{
    char    *fullstr;
    char    *tmp;
    int     i;

    i = -1;
    fullstr = ft_strtrim(s_cmd->full, " ");
    while(fullstr[++i] != '\0')
    {
        if (fullstr[i] == ' ')
        {
            s_cmd->cmd = ft_substr(fullstr, 0, i);
            if (s_cmd->cmd[0] == '$')
                convert_env_to_cmd(s_cmd, s_env);
            break;
        }
    }
    tmp = s_cmd->full;
    s_cmd->full = ft_strdup(&fullstr[i]);
    free(tmp);
    free(fullstr);
}

t_args	*ft_lastarg(t_args *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (lst);
}

void    get_the_arg(t_cmd *s_cmd, char *fullstr, int *i)
{
    int j;
    t_args  *tmp;
    t_args  *args;
    int     quote;
    int     dquotes;

    j = *i;
    quote = 0;
    dquotes = 0;
    if((args = (t_args*)malloc(sizeof(t_args))) == NULL)
        error();
    while (fullstr[j] != '\0')
    {
        if (fullstr[j] == 34 || fullstr[j] == 39)
            check_quotes(fullstr[j], &quote, &dquotes);
        if (fullstr[j] == ' ' && quote == 0 && dquotes == 0)
            break;
        j++;
    }
    args->arg = ft_substr(fullstr, *i, j - (*i));
    args->next = NULL;
    if((tmp = ft_lastarg(s_cmd->args)) == NULL)
        s_cmd->args = args;
    else
        tmp->next = args;
    free(fullstr);
    *i = j;
}

void    get_args(t_cmd *s_cmd, t_env **s_env)
{
    char    *fullstr;
    int     i;

    i = -1;
    fullstr = s_cmd->full;
    while(fullstr[++i] != '\0')
        get_the_arg(s_cmd, ft_strtrim(&fullstr[i], " "), &i);
}

void    cmd_parser(t_cmd **s_cmd, t_env **s_env)
{
    t_cmd   *tmp;
    
    tmp = *s_cmd;
    while (tmp)
    {
        get_the_cmd(tmp, s_env);
        get_args(tmp, s_env);
        tmp = tmp->next;
    }
}