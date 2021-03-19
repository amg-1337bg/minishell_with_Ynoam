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

int    ft_creat_file(char *filename)
{
    return (open(filename, O_WRONLY |  O_CREAT | O_TRUNC, 00644));
}
int     pipe_count(t_cmd *command)
{
    int i;

    i = 0;
    while (command->pipe != NULL)
    {
        command = command->pipe;
        i++;
    }
    return (i);
}

int     is_builtin(char *command)
{
	if (ft_strncmp(command, "echo", ft_strlen(command)))
    	return (TRUE);
	else if (ft_strncmp(command, "cd", ft_strlen(command)))
    	return (TRUE);
	else if (ft_strncmp(command, "export", ft_strlen(command)))
    	return (TRUE);
	else if (ft_strncmp(command, "env", ft_strlen(command)))
    	return (TRUE);
	else if (ft_strncmp(command, "exit", ft_strlen(command)))
    	return (TRUE);
	return (FALSE);
}
int     exec_builtin(t_cmd *cmds)
{
	printf("i am a built in command\n");
    return (0);
}

int     exec_pipe(t_cmd *cmds)
{
    return (0);
}

int     exec_normal(t_cmd *cmds)
{

	return (0);
}
int     execute(t_cmd *cmds, char **env)
{
    int ret;

	printf("hello1\n");
    ret = 0;


    while(cmds !=  NULL)
    {
        if (cmds->pipe != NULL)// piped commands
            ret = exec_pipe(cmds);
        else if (is_builtin(cmds->cmd) == TRUE)// Normal and builtin command
            ret = exec_builtin(cmds);
        else // normal and not builtin command
            ret = exec_normal(cmds);
        cmds = cmds->next;
    }
    return (ret);
}