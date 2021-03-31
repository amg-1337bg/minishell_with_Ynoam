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

int		return_value(int ret)
{
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	else if (WIFSTOPPED(ret))
		return (WSTOPSIG(ret));
	else if (WIFSIGNALED(ret))
		return (WTERMSIG(ret));
	return (0);
}
void    close_pipe(int fd[])
{
    close(fd[0]);
    close(fd[1]);
}

int		creat_file_or_openit(char *filename, int trunc)
{
    return (open(filename, O_WRONLY |  O_CREAT | trunc, 00644));
}

int		open_file_for_read(char *filename)
{
	return (open(filename, O_RDONLY));
}

int		create_files(t_files *files)
{
	int	ret;

	if (fork() == 0)
	{
		while (files)
		{
			if (files->type[0] == '>')
				creat_file_or_openit(files->file, 0);
			else if (files->type[0] == '>' && files->type[1] == '>')
				creat_file_or_openit(files->file, 0);
			else if (files->type[0] == '<')
				if (open_file_for_read(files->file) == -1)
				{
					put_error(strerror(errno), files->file);
					exit(1);
				}
			files = files->next;
		}
		exit(0);
	}
	wait(&ret);
	return (return_value(ret));
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
    char    *onepath;
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
        else if (fork() == 0)
        {
            execve(cmd->cmd, create_args(cmd), env);
			put_error(strerror(errno), cmd->cmd);
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
                onepath = ft_strjoin(ft_strjoin(paths[i], "/"), cmd->cmd);
                char **str;
                str = create_args(cmd);
                execve(onepath, create_args(cmd), env);
                ft_free(&onepath);
                i++;
            }
			put_error("command not found", cmd->cmd);
			exit(127);
        }
        wait(&ret);
		return (return_value(ret));
    }
}

int		execute(t_cmd *cmds, char **env)
{
    int ret;

    ret = 0;
    while(cmds !=  NULL)
    {
        if (cmds->pipe)// piped commands
        {
            ret = exec_pipe(cmds);
        }
        else if (cmds->cmd && is_builtin(cmds->cmd))// Normal and builtin command
        {
            ret = exec_builtin(cmds);
        }
        else if (cmds->cmd && !is_builtin(cmds->cmd))// normal and not builtin command
        {
            ret = exec_normal(cmds, env);
        }
		else if (cmds->cmd == NULL)
		{
			printf("work1\n");
			ret = create_files(cmds->files);
		}
        cmds = cmds->next;
    }
    return (ret);
}
