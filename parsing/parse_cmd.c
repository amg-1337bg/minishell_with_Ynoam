/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 09:31:59 by bamghoug          #+#    #+#             */
/*   Updated: 2021/05/29 14:33:05 by bamghoug         ###   ########.fr       */
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

// char    *get_redir_type(char *fullstr, int *j)
// {
//     char    *ret;

//     if(fullstr)
// }

int    get_file(t_cmd *s_cmd, char *fullstr, int j, int *i)
{
    t_files *fill;
    t_files *tmp;
    int     path_begin;

    // if((fill = (t_files*)malloc(sizeof(t_files))) == NULL)
    //     error();
    // if (fullstr[j] == '<')
    //     fill->type = ft_strdup("<");
    // else if (fullstr[j] == '>')
    // {
    //     if(fullstr[j + 1] == '>')
    //     {
    //         fill->type = ft_strdup(">>");
    //         j++;
    //     }
    //     else
    //         fill->type = ft_strdup(">");
    // }
    // j++;
    // j += space_count(&fullstr[j]);
    // path_begin = j;
    // while (fullstr[j] != '\0')
    // {
    //     if(fullstr[j] == ' ' || fullstr[j] == '<' || fullstr[j] == '>' || fullstr[j] == '|')
    //         break;
    //     j++;
    // }
    // fill->file = ft_substr(fullstr, path_begin, j - path_begin);
    // fill->next = NULL;
    // if (ft_strlen(fill->file) == 0)
    //     return -1;
    // if((tmp = ft_lastfile(s_cmd->files)) == NULL)
    //     s_cmd->files = fill;
    // else
    //     tmp->next = fill;
    // j += space_count(&fullstr[j]);
    // *i = j - 1;
    return (0);
}

void    initializ_pipecmd(t_cmd **pipe_cmd, t_cmd *s_cmd)
{
    if ((*pipe_cmd = (t_cmd*)malloc(sizeof(t_cmd))) == NULL)
        error();
    pipe_cmd[0]->cmd = NULL;
    pipe_cmd[0]->args = NULL;
    pipe_cmd[0]->full = ft_strdup(s_cmd->full);
    pipe_cmd[0]->files = NULL;
    pipe_cmd[0]->pipe = NULL;
    pipe_cmd[0]->next = NULL;
}

int    get_pipe_cmd(t_cmd *s_cmd, int *i)
{
    t_cmd   *pipe_cmd;
    t_cmd   *tmp_cmd;
    int     from;
    int     just_char;
    
    from = -1;
    just_char = -1;
    (*i) += space_count(&s_cmd->full[*i + 1]);
    initializ_pipecmd(&pipe_cmd, s_cmd);
    while(pipe_cmd->full[++(*i)] != '\0')
    {
        if(from == -1)
            from = (*i);
        if (pipe_cmd->full[*i] == '\'' || pipe_cmd->full[*i] == '"')
            quote_detected(pipe_cmd->full, i, just_char);
        else if (pipe_cmd->full[*i] == '>' || pipe_cmd->full[*i] == '<')
        {
            if (get_redirection(pipe_cmd, i, from, just_char) != 0)
                from = -1;
        }
        else if(s_cmd->full[*i] == ' ' && (s_cmd->full[(*i) - 1] != '\\' || just_char == (*i) - 1))
        {
            if (get_cmd_args(pipe_cmd, from, i) != 0)
            {
                printed_errors(Syntax_error, &pipe_cmd->full[*i]);
                return -1;
            }
            from = -1;
        }
        else if (pipe_cmd->full[(*i)] == '|' && (pipe_cmd->full[(*i) - 1] != '\\' || just_char == (*i) - 1))
        {
            if (from == (*i))
            {
                from = -1;
                (*i) -= 1;
            }
            break;
        }
        else if (pipe_cmd->full[*i] == '\\' && pipe_cmd->full[(*i) + 1] == '\\')
            just_char = (*i) + 1;
    }
    get_the_rest(pipe_cmd, i, from);
    if((tmp_cmd = ft_lstcmd(s_cmd->pipe)) == NULL)
        s_cmd->pipe = pipe_cmd;
    else
        tmp_cmd->next = pipe_cmd;
    return (0);
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

int    get_cmd_args(t_cmd *s_cmd, int from, int *i)
{
    t_args  *args;
    t_args  *tmp_arg;
    char    *str;
    
    str = ft_substr(s_cmd->full, from, (*i) - from);
    if (s_cmd->cmd == NULL)
    {
        s_cmd->cmd = str;
    }
    else
    {
        if((args = (t_args*)malloc(sizeof(t_args))) == NULL)
            error();
        args->arg = str;
        args->next = NULL;
        if((tmp_arg = ft_lastarg(s_cmd->args)) == NULL)
            s_cmd->args = args;
        else
            tmp_arg->next = args;
    }
    *i += space_count(&s_cmd->full[*i]) - 1;
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
            quote_detected(&s_cmd->full[*i], i, just_char);
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

int     get_redirection(t_cmd *s_cmd, int *i, int from, int just_char)
{
    t_files *fill;
    t_files *tmp;

    if(*i == 0 || s_cmd->full[*i - 1] != '\\' || (s_cmd->full[*i - 1] == '\\' && just_char == *i - 1))
    {
        if (from != (*i))
        {
            if (get_cmd_args(s_cmd, from, i) != 0);
            // {
            //     printed_errors(Syntax_error, &s_cmd->full[i]);
            //     return -1;
            // }
            (*i)++;
        }
        fill = (t_files*)malloc(sizeof(t_files));
        fill->type = get_redir_type(s_cmd, i);
        fill->file = get_filename(s_cmd, i, just_char);
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

int     pipe_function(t_cmd *s_cmd, int *i, int from, int just_char)
{
    if(*i == 0 || s_cmd->full[*i - 1] != '\\' || (s_cmd->full[*i - 1] == '\\' && just_char == *i - 1))
    {
        if (from != (*i))
        {
            if (get_cmd_args(s_cmd, from, i) != 0);
            // {
            //     printed_errors(Syntax_error, &s_cmd->full[i]);
            //     return -1;
            // }
            (*i)++;
        }
        if(get_pipe_cmd(s_cmd, i) != 0)
            return -1;
        return (1);
    }
    return (0);
}

int     get_the_rest(t_cmd *s_cmd, int *i, int from)
{
    if(from != -1)
    {
        if (get_cmd_args(s_cmd, from, i) != 0)
        {
            printed_errors(Syntax_error, &s_cmd->full[*i]);
            return (-1);
        }
    }
    return (0);
}

int     get_args(t_cmd *s_cmd)
{
    int     i;
    int     from;
    int     just_char;

    i = -1;
    from = -1;
    just_char = -1;
    while(s_cmd->full[++i] != '\0')
    {
        if(from == -1)
            from = i;
        if (s_cmd->full[i] == '\'' || s_cmd->full[i] == '"')
            quote_detected(s_cmd->full, &i, just_char);
        else if (s_cmd->full[i] == '>' || s_cmd->full[i] == '<')
        {
            if (get_redirection(s_cmd, &i, from, just_char) != 0)
                from = -1;
        }
        else if(s_cmd->full[i] == ' ' && (s_cmd->full[i - 1] != '\\' || just_char == i - 1))
        {
            if (get_cmd_args(s_cmd, from, &i) != 0)
            {
                printed_errors(Syntax_error, &s_cmd->full[i]);
                return -1;
            }
            from = -1;
        }
        else if (s_cmd->full[i] == '|')
        {
            if(pipe_function(s_cmd, &i, from, just_char) == 1)
                from = -1;
        }
        else if (s_cmd->full[i] == '\\' && s_cmd->full[i + 1] == '\\')
            just_char = i + 1;
    }
    get_the_rest(s_cmd, &i, from);
    // if(from != -1)
    // {
    //     if (get_cmd_args(s_cmd, from, &i) != 0)
    //     {
    //         printed_errors(Syntax_error, &s_cmd->full[i]);
    //         return (-1);
    //     }
    // }
    return (0);
}

int    cmd_parser(t_cmd **s_cmd, t_env *s_env)
{
    t_cmd   *tmp;
    int     error;
    char    *tofree;
    char    *i;
    tmp = s_cmd[0];
    while (tmp)
    {
        tofree = tmp->full;
        tmp->full = ft_strtrim(tmp->full, " ");
        free(tofree);
        if ((error = get_args(tmp)) != 0)
            return (error);
        // printf("hello %s\n", tmp->args->arg);
        // if (clean_replace(tmp, s_env) != 0)
        //     return (-1);
        tmp = tmp->next;
    }
    return (0);
}