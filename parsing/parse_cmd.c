/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:31:59 by bamghoug          #+#    #+#             */
/*   Updated: 2021/03/16 14:59:11 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    convert_cmd_to_env(t_cmd *s_cmd, t_env **s_env)
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
        convert_cmd_to_env(s_cmd, s_env);
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

void    get_file(t_cmd *s_cmd, char *fullstr, int j, int *i)
{
    t_files *fill;
    t_files *tmp;
    int     path_begin;

    if((fill = (t_files*)malloc(sizeof(t_files))) == NULL)
        error();
    if (fullstr[j] == '<')
        fill->type = ft_strdup("<");
    else if (fullstr[j] == '>')
    {
        if(fullstr[j + 1] == '>')
        {
            fill->type = ft_strdup(">>");
            j++;
        }
        else
            fill->type = ft_strdup(">");
    }
    j++;
    j += space_count(&fullstr[j]);
    path_begin = j;
    while (fullstr[j] != '\0')
    {
        if(fullstr[j] == ' ' || fullstr[j] == '<' || fullstr[j] == '>' || fullstr[j] == '|')
            break;
        j++;
    }
    fill->file = ft_substr(fullstr, path_begin, j - path_begin);
    fill->next = NULL;
    if((tmp = ft_lastfile(s_cmd->files)) == NULL)
        s_cmd->files = fill;
    else
        tmp->next = fill;
    j += space_count(&fullstr[j]);
    *i = j - 1;
}

void    get_pipe_cmd(t_cmd *s_cmd, t_env **s_env, int *i)
{
    t_cmd   *pipe_cmd;
    t_cmd   *tmp_cmd;
    int     quote;
    int     dquote;
    int     from;

    quote = 0;
    dquote = 0;
    from = -1;
    if ((pipe_cmd = (t_cmd*)malloc(sizeof(t_cmd))) == NULL)
        error();
    pipe_cmd->cmd = NULL;
    pipe_cmd->args = NULL;
    pipe_cmd->full = ft_strdup(s_cmd->full);
    pipe_cmd->files = NULL;
    pipe_cmd->pipe = NULL;
    pipe_cmd->next = NULL;
    (*i) += space_count(&pipe_cmd->full[*i + 1]);
    while(pipe_cmd->full[++(*i)] != '\0')
    {
        if(from == -1)
            from = *i;
        if (pipe_cmd->full[(*i)] == '\'' || pipe_cmd->full[(*i)] == '"')
            check_quotes(s_cmd->full[(*i)], &quote, &dquote);
        else if ((pipe_cmd->full[(*i)] == '>' || pipe_cmd->full[(*i)] == '<') && quote == 0 && dquote == 0)
        {
            if (from != (*i))
            {
                get_cmd_args(pipe_cmd, s_env, from, i);
                from = ++(*i);
            }
            get_file(pipe_cmd, pipe_cmd->full, from, i);
            from = -1;
        }
        else if(s_cmd->full[(*i)] == ' ' && quote == 0 && dquote == 0)
        {
            get_cmd_args(pipe_cmd, s_env, from, i);
            from = -1;
        }
        else if (s_cmd->full[(*i)] == '|' && quote == 0 && dquote == 0)
            break;
    }
    if(from != -1)
        get_cmd_args(pipe_cmd, s_env, from, i);
    if((tmp_cmd = ft_lstcmd(s_cmd->pipe)) == NULL)
        s_cmd->pipe = pipe_cmd;
    else
        tmp_cmd->next = pipe_cmd;
    // (*i) -= 1;
}

// void    get_the_arg(t_cmd *s_cmd, t_env **s_env, char *fullstr, int *i)
// {
//     int j;
//     t_args  *tmp;
//     t_args  *arg;
//     int     quote;
//     int     dquotes;

//     j = *i;
//     quote = 0;
//     dquotes = 0;
//     while (fullstr[j] != '\0')
//     {
//         if ((fullstr[j] == 34 || fullstr[j] == 39) && fullstr[j - 1] != '\\')
//             check_quotes(fullstr[j], &quote, &dquotes);
//         else if (fullstr[j] == ' ' && quote == 0 && dquotes == 0)
//             break;
//         else if ((fullstr[j] == '>' || fullstr[j] == '<') && quote == 0 && dquotes == 0)
//         {
//             get_file(s_cmd, &fullstr[j], i);
//             return ;
//         }
//         else if (fullstr[j] == '|' && quote == 0 && dquotes == 0)
//         {
//             get_pipe_cmd(s_cmd, s_env, fullstr, &j);
//             *i = ft_strlen(fullstr) - 1;
//             return ;
//         }
//         j++;
//     }
//     if((arg = (t_args*)malloc(sizeof(t_args))) == NULL)
//         error();
//     arg->arg = ft_substr(fullstr, *i, j - (*i));
//     arg->next = NULL;
//     if((tmp = ft_lastarg(s_cmd->args)) == NULL)
//         s_cmd->args = arg;
//     else
//         tmp->next = arg;
//     *i = j;
// }

void    get_cmd_args(t_cmd *s_cmd, t_env **env, int from, int *i)
{
    t_args *args;
    t_args *tmp_arg;
    
    if (s_cmd->cmd == NULL)
        s_cmd->cmd = ft_substr(s_cmd->full, from, (*i) - from);
    else
    {
        if((args = (t_args*)malloc(sizeof(t_args))) == NULL)
            error();
        args->arg = ft_substr(s_cmd->full, from, (*i) - from);
        args->next = NULL;
        if((tmp_arg = ft_lastarg(s_cmd->args)) == NULL)
            s_cmd->args = args;
        else
            tmp_arg->next = args;
    }
    *i += space_count(&s_cmd->full[*i]) - 1;
}

void    get_args(t_cmd *s_cmd, t_env **s_env)
{
    int     i;
    int     quote;
    int     dquote;
    int     from;

    i = -1;
    quote = 0;
    dquote = 0;
    from = -1;
    while(s_cmd->full[++i] != '\0')
    {
        if(from == -1)
            from = i;
        if (s_cmd->full[i] == '\'' || s_cmd->full[i] == '"')
            check_quotes(s_cmd->full[i], &quote, &dquote);
        else if ((s_cmd->full[i] == '>' || s_cmd->full[i] == '<') && quote == 0 && dquote == 0)
        {
            if (from != i)
            {
                get_cmd_args(s_cmd, s_env, from, &i);
                from = ++i;
            }
            get_file(s_cmd, s_cmd->full, from, &i);
            from = -1;
        }
        else if(s_cmd->full[i] == ' ' && quote == 0 && dquote == 0)
        {
            get_cmd_args(s_cmd, s_env, from, &i);
            from = -1;
        }
        else if (s_cmd->full[i] == '|' && quote == 0 && dquote == 0)
        {
            get_pipe_cmd(s_cmd, s_env, &i);
            from = -1;
        }
    }
    if(from != -1)
        get_cmd_args(s_cmd, s_env, from, &i);
}

void    cmd_parser(t_cmd **s_cmd, t_env **s_env)
{
    t_cmd   *tmp;
    
    tmp = *s_cmd;
    while (tmp)
    {
        get_args(tmp, s_env);
        clean_replace(tmp, s_env);
        // get_the_cmd(tmp, s_env);
        // get_args(tmp, s_env);
        tmp = tmp->next;
    }
}