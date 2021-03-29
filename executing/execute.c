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

void    close_pipe(int fd[])
{
    close(fd[0]);
    close(fd[1]);
}

int    ft_creat_file(char *filename, int trunc)
{
    return (open(filename, O_WRONLY |  O_CREAT | trunc, 00644));
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
    if (!ft_strncmp(command, "echo", ft_strlen("echo") + 1))
        return (1);
    else if (!ft_strncmp(command, "cd", ft_strlen("cd") + 1))
        return (1);
    else if (!ft_strncmp(command, "pwd", ft_strlen("pwd") + 1))
        return (1);
    else if (!ft_strncmp(command, "export", ft_strlen("export") + 1))
        return (1);
    else if (!ft_strncmp(command, "unset", ft_strlen("unset") + 1))
        return (1);
    else if (!ft_strncmp(command, "env", ft_strlen("env") + 1))
        return (1);
    else if (!ft_strncmp(command, "exit", ft_strlen("exit") + 1))
        return (1);
    
    return (0);
}
int     exec_builtin(t_cmd *cmds)
{
    printf("i am a built in command\n");
    return (0);
}

int     exec_pipe(t_cmd *cmds)
{
    printf("there is a pipe\n");
    return (0);
}

int     is_path(char *cmd)
{
    int i;

    i = ft_strlen(cmd);
    if ((i > 2 && cmd[0] == '.' && cmd[1] == '/') || (i > 3 && cmd[0] == '.' && cmd[1] == '/'))
    {
        return(1);
    }

}
int     exec_normal(t_cmd *cmds, char **env)
{
    int pid;
    int fd[2];

    if (is_path(cmds->cmd)) // command not in path variable
    {
        pipe(fd);
        if (fork() == 0)
        {

            close_pipe(fd);
        }
        close_pipe(fd);
    }
    else // command in path variable
    {
        return (127);
    }
    return (0);
}

int     execute(t_cmd *cmds, char **env)
{
    int ret;

    ret = 0;
    while(cmds !=  NULL)
    {
        if (cmds->pipe)// piped commands
        {
            ret = exec_pipe(cmds);
        }
        else if (is_builtin(cmds->cmd) == 1)// Normal and builtin command
        {
            ret = exec_builtin(cmds);
        }
        else // normal and not builtin command
        {
            ret = exec_normal(cmds, env);
        }
        cmds = cmds->next;
    }
    return (ret);
}