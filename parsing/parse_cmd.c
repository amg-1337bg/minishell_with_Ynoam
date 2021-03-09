/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:31:59 by bamghoug          #+#    #+#             */
/*   Updated: 2021/03/09 17:01:32 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
            break;
    }
    s_cmd->cmd = ft_substr(fullstr, 0, i);
    if (s_cmd->cmd[0] == '$')
        convert_env_to_cmd(s_cmd, s_env);
    tmp = s_cmd->full;
    s_cmd->full = ft_strtrim(&fullstr[i], " ");
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

char     *get_file_path(char *fullstr)
{
    char    *ret;

    ret = ft_strtrim(fullstr, " ");
    return (ret);
}

int     space_count(char *str)
{
    int i;
    
    i = 0;
    while (str[i] != '\0' && str[i] == ' ')
        i++;
    return (i);
}

t_files	*ft_lastfile(t_files *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (lst);
}

void    get_file(t_cmd *s_cmd, char *fullstr, int *i)
{
    t_files *fill;
    t_files *tmp;
    int     j;
    int     path_begin;

    if((fill = (t_files*)malloc(sizeof(t_files))) == NULL)
        error();
    j = 1;
    if (fullstr[0] == '<')
        fill->type = ft_strdup("<");
    else if (fullstr[0] == '>')
    {
        if(fullstr[1] == '>')
        {
            fill->type = ft_strdup(">>");
            j++;            
        }
        else
            fill->type = ft_strdup(">");
    }
    j += space_count(&fullstr[j]);
    path_begin = j;
    while (fullstr[j] != '\0')
    {
        if(fullstr[j] == ' ')
            break;
        j++;
    }
    fill->file = ft_substr(fullstr, path_begin, j - path_begin);
    fill->next = NULL;
    if((tmp = ft_lastfile(s_cmd->files)) == NULL)
        s_cmd->files = fill;
    else
        tmp->next = fill;
    *i += j;
}

void    get_the_arg(t_cmd *s_cmd, char *fullstr, int *i)
{
    int j;
    t_args  *tmp;
    t_args  *arg;
    int     quote;
    int     dquotes;

    j = *i;
    quote = 0;
    dquotes = 0;
    if((arg = (t_args*)malloc(sizeof(t_args))) == NULL)
        error();
    while (fullstr[j] != '\0')
    {
        if (fullstr[j] == 34 || fullstr[j] == 39)
            check_quotes(fullstr[j], &quote, &dquotes);
        else if (fullstr[j] == ' ' && quote == 0 && dquotes == 0)
            break;
        else if ((fullstr[j] == '>' || fullstr[j] == '<') && quote == 0 && dquotes == 0)
        {
            get_file(s_cmd, &fullstr[j], i);
            return ;
        }
        j++;
    }
    arg->arg = ft_substr(fullstr, *i, j - (*i));
    arg->next = NULL;
    if((tmp = ft_lastarg(s_cmd->args)) == NULL)
        s_cmd->args = arg;
    else
        tmp->next = arg;
    *i = j;
}

void    get_args(t_cmd *s_cmd, t_env **s_env)
{
    char    *fullstr;
    int     i;

    i = -1;
    fullstr = s_cmd->full;
    while(fullstr[++i] != '\0')
        get_the_arg(s_cmd, fullstr, &i);
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