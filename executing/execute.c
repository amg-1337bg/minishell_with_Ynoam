/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:30:36 by ynoam             #+#    #+#             */
/*   Updated: 2021/03/06 20:49:20 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int     execute(t_cmd *cmds, char **env)
{
    while (cmds != NULL)
    {
        // // if there is a pipe
        // if (cmds->pipe == 1)
        // {
        //     int fd[2];
        //     pipe(fd);
        // }
        // // fork
        // int pid = fork();
        // if (pid == 0)
        // {
        //     // child 
        //     // execute
        //     execve();
        // }
        // else
        // {
        //     // parent
        // }
        









        // repeat
        cmds = cmds->next;
    }
    return (0);
}