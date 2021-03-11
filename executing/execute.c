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


void handle_sigint(int sig) 
{ 
    printf("Caught signal %d\n", sig); 
    exit(0);
}
void    ft_creat_file(char *filename)
{
    open(filename, O_WRONLY |  O_CREAT | O_TRUNC, 00644);
}
int     execute(t_cmd *cmds, char **env)
{



    return (0);
}