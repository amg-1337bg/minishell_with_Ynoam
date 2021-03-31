/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:30:36 by ynoam             #+#    #+#             */
/*   Updated: 2021/03/29 12:42:15 by ynoam            ###   ########.fr       */
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
	if ((i >= 2 && cmd[0] == '.' && cmd[1] == '/') || (i >= 3 && cmd[0] == '.' &&
				cmd[1] == '.' && cmd[2] == '/') || (i >= 1 && cmd[0] == '/'))
		return (1);
	return (0);
}

char	**search_env_for_path(char **env)
{
	int	i;

	i = 0;
	while(env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return(ft_split(&(env[i][5]), ':'));
		i++;
	}
	return (NULL);
}

char    **create_args(t_cmd *cmd)
{
    t_args  *tmp_args;
    char    **argv;
    int     i;
    int     j;

    tmp_args = cmd->args;
    i = 1;
    while(tmp_args)
    {
        tmp_args = tmp_args->next;
        i++;
    }
    tmp_args = cmd->args;
    argv = malloc((i + 1) * sizeof(char*));
    argv[0] = cmd->cmd;
    j = 1;
    while(j < i)
    {
        argv[j] = tmp_args->arg;
        tmp_args = tmp_args->next;
        j++;
    }
    argv[j] = NULL;
    return (argv);
}

int     exec_normal(t_cmd *cmd, char **env)
{
    char    **paths;
    char    *path;
    int     ret;
    DIR     *dir;
    int i = 0;

    if (is_path(cmd->cmd)) // command not in path variable
    {
        if ((dir = opendir(cmd->cmd)) != NULL)
        {
            put_error("is a directory", cmd->cmd);
            closedir(dir);
            return (126);
        }
        if (fork() == 0)
        {
            execve(cmd->cmd, create_args(cmd), env);
			put_error("No such file or directory", cmd->cmd);
			exit(127);
        }
        wait(&ret);
        return (ret);
    }
    else // command in path variable
    {
        if (fork() == 0)
        {
            paths = search_env_for_path(env); // LEAK: search return
            while(paths[i])
            {
                path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd->cmd);
                char **str;
                str = create_args(cmd);
                execve(path, create_args(cmd), env);
                // ft_free(path);
                i++;
            }
			put_error("command not found", cmd->cmd);
			exit(127);
        }
        wait(&ret);
    }
    return (ret);
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
