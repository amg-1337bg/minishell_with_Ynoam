/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:30:36 by ynoam             #+#    #+#             */
/*   Updated: 2021/03/07 18:14:27 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int     how_much_pipes(t_cmd *cmds)
{
        int i;

        i = 0;
        while(cmds->pipe == 1)
            i++;
        return (i);
}

void    ft_creat_file(char *filename)
{
    open(filename, O_WRONLY |  O_CREAT | O_TRUNC, 00644);
}
int     execute(t_cmd *cmds, char **env)
{
        // how_much_semicolon(cmds);
        while(1)
        {
            int i;
            i = how_much_pipes(cmds);
            int fd[i][2];
            
            while(i--)
            {

            }

        }
        










    return (0);
}