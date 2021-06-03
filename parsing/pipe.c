/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 11:40:32 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/03 11:42:34 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     pipe_function(t_cmd *s_cmd, int *i, int *from, int just_char)
{
    char    *tmp;
    
    if(*i == 0 || s_cmd->full[*i - 1] != '\\' || (s_cmd->full[*i - 1] == '\\' && just_char == *i - 1))
    {
        if (*from != (*i))
        {
            get_cmd_args(s_cmd, *from, i);
            (*i)++;
        }
        tmp = ft_strdup(&s_cmd->full[(*i) + 1]);
        if (ft_strlen(tmp) == 0)
        {
            printed_errors(No_MultilineCmd);
            return (-1);
        }
        (*i)++;
        if(get_pipe_cmd(s_cmd, i) != 0)
            return 0;
        *from = -1;
        return (1);
    }
    return (0);
}

int    get_pipe_cmd(t_cmd *s_cmd, int *i)
{
    t_cmd   *pipe_cmd;
    t_cmd   *tmp_cmd;
    int     from;
    int     just_char;
    
    from = -1;
    just_char = -1;
    (*i) += space_count(&s_cmd->full[*i + 1]) - 1;
    initializ_pipecmd(&pipe_cmd, s_cmd);
    while(pipe_cmd->full[++(*i)] != '\0')
    {
        if (pipe_checker(pipe_cmd, i, &from, &just_char) == 1)
            break ;
    }
    get_the_rest(pipe_cmd, i, from);
    if((tmp_cmd = ft_lstcmd(s_cmd->pipe)) == NULL)
        s_cmd->pipe = pipe_cmd;
    else
        tmp_cmd->next = pipe_cmd;
    return (0);
}

int    pipe_checker(t_cmd *pipe_cmd, int *i, int *from, int *just_char)
{
    if((*from) == -1)
        (*from) = (*i);
    if (pipe_cmd->full[*i] == '\'' || pipe_cmd->full[*i] == '"')
        quote_detected(pipe_cmd->full, i, *just_char);
    else if (pipe_cmd->full[*i] == '>' || pipe_cmd->full[*i] == '<')
    {
        if (get_redirection(pipe_cmd, i, (*from), *just_char) != 0)
            (*from) = -1;
    }
    else if(pipe_cmd->full[*i] == ' ' && (pipe_cmd->full[(*i) - 1] != '\\' || *just_char == (*i) - 1))
    {
        get_cmd_args(pipe_cmd, (*from), i);
        (*from) = -1;
    }
    else if (pipe_cmd->full[(*i)] == '|' && (pipe_cmd->full[(*i) - 1] != '\\' || *just_char == (*i) - 1))
    {
        if ((*from) == (*i))
        {
            (*from) = -1;
            (*i) -= 1;
        }
        return (1);
    }
    else if (pipe_cmd->full[*i] == '\\' && pipe_cmd->full[(*i) + 1] == '\\')
        (*just_char) = (*i) + 1;
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