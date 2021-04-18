/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:30:36 by ynoam             #+#    #+#             */
/*   Updated: 2021/04/18 17:40:40 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	creat_file_or_openit(char *filename, int trunc)
{
	return (open(filename, O_WRONLY | O_CREAT | trunc, 00644));
}

int	open_file_for_read(char *filename, int i)
{
	int	j;

	if (i == 0)
		return (open(filename, O_RDONLY));
	if (i == 1)
	{
		j = open(filename, O_RDONLY);
		if (j == -1)
			return (-1);
		close(j);
	}
}

void	assign_stdin_stdout(char *stdoutf, char *stdinf, int trunc, int *fd)
{
	if (stdoutf && !trunc)
		fd[1] = creat_file_or_openit(stdoutf, O_TRUNC);
	else if (stdoutf && trunc)
		fd[1] = creat_file_or_openit(stdoutf, O_APPEND);
	else if (stdinf)
		fd[0] = open_file_for_read(stdinf, 0);
}

void	change_stdin_stdout(t_files *files, int *fd)
{
	char	*stdin_file;
	char	*stdout_file;
	int		trunc;

	fd[0] = 0;
	fd[1] = 1;
	trunc = 0;
	stdout_file = NULL;
	stdin_file = NULL;
	while (files)
	{
		if (files->type[0] == '>' && files->type[1] == 0)
		{
			trunc = 0;
			stdout_file = files->file;
		}
		else if (files->type[0] == '>' && files->type[1] == '>' && ++trunc)
			stdout_file = files->file;
		else if (files->type[0] == '<')
			stdin_file = files->file;
		files = files->next;
	}
	assign_stdin_stdout(stdout_file, stdin_file, trunc, fd);
}

int	return_value(int ret)
{
	if (WIFEXITED(ret))
		return (WEXITSTATUS(ret));
	else if (WIFSTOPPED(ret))
		return (WSTOPSIG(ret));
	else if (WIFSIGNALED(ret))
		return (WTERMSIG(ret));
	return (0);
}

void	close_pipe(int fd[])
{
	close(fd[0]);
	close(fd[1]);
}

char	**create_args(t_cmd *cmd)
{
	t_args	*tmp_args;
	char	**argv;
	int		i;
	int		j;

	tmp_args = cmd->args;
	i = 1;
	while (tmp_args)
	{
		tmp_args = tmp_args->next;
		i++;
	}
	tmp_args = cmd->args;
	argv = malloc((i + 1) * sizeof(char *));
	argv[0] = cmd->cmd;
	j = 1;
	while (j < i)
	{
		argv[j] = tmp_args->arg;
		tmp_args = tmp_args->next;
		j++;
	}
	argv[j] = NULL;
	return (argv);
}

int	create_files(t_files *files)
{
	while (files)
	{
		if (files->type[0] == '>')
		{
			if (creat_file_or_openit(files->file, 0) == -1)
			{
				put_error(strerror(errno), files->file);
				return (1);
			}
		}
		else if (files->type[0] == '<')
		{
			if (open_file_for_read(files->file, 1) == -1)
			{
				put_error(strerror(errno), files->file);
				return (1);
			}
		}
		files = files->next;
	}
	return (0);
}

int	is_builtin(char *command)
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

void	close_fds(int *fd)
{
	if (fd[0] != 0)
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
	free(fd);
}

int	exec_builtin(t_cmd *cmd, t_env *env)
{
	int	*fd;
	int	ret;

	fd = malloc(sizeof(int) * 2);
	ret = 0;
	change_stdin_stdout(cmd->files, fd);
	if (!ft_strncmp(cmd->cmd, "echo", ft_strlen("echo") + 1))
		ret = ft_echo(create_args(cmd), fd);
	else if (!ft_strncmp(cmd->cmd, "cd", ft_strlen("cd") + 1))
		ret = cd(env, cmd->args);
	else if (!ft_strncmp(cmd->cmd, "pwd", ft_strlen("pwd") + 1))
		ret = pwd(fd);
	else if (!ft_strncmp(cmd->cmd, "export", ft_strlen("export") + 1))
		ret = export(env, create_args(cmd), fd);
	else if (!ft_strncmp(cmd->cmd, "unset", ft_strlen("unset") + 1))
		ret = unset(env, create_args(cmd));
	else if (!ft_strncmp(cmd->cmd, "env", ft_strlen("env") + 1))
		ret = ft_env(env, fd);
	else if (!ft_strncmp(cmd->cmd, "exit", ft_strlen("exit") + 1))
		ret = ft_exit(create_args(cmd));
	close_fds(fd);
	return (ret);
}

int	is_path(char *cmd)
{
	int	i;

	i = ft_strlen(cmd);
	if ((i >= 2 && cmd[0] == '.' && cmd[1] == '/') || (i >= 3 && cmd[0] == '.' && \
				cmd[1] == '.' && cmd[2] == '/') || (i >= 1 && cmd[0] == '/'))
		return (1);
	return (0);
}

int	exec_normal2(t_cmd *cmd, t_env *env)
{
	int	*fd;
	DIR	*dir;

	fd = malloc(sizeof(int) * 2);
	if ((dir = opendir(cmd->cmd)) != NULL)
	{
		put_error("is a directory", cmd->cmd);
		closedir(dir);
		free(fd);
		return (126);
	}
	else
	{
		change_stdin_stdout(cmd->files, fd);
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		execve(cmd->cmd, create_args(cmd), create_envp(env, cmd->cmd));
		put_error(strerror(errno), cmd->cmd);
		free(fd);
		return (127);
	}
}

int	ft_free_double(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		ft_free(&(ptr[i]));
		i++;
	}
	free(ptr[i]);
	free(ptr);
	return (1);
}

void	search_for_path_and_exec(t_cmd *cmd, t_env *env)
{
	char	**paths;
	char	**str;
	char	*onepath;
	char	*str2;
	int		i;

	i = 0;
	paths = ft_split(search_env(env, "PATH"), ':');
	str = create_args(cmd);
	str2 = ft_strjoin("/", cmd->cmd);
	while (paths[i])
	{
		onepath = ft_strjoin(paths[i], str2);
		execve(onepath, str, create_envp(env, onepath));
		ft_free(&onepath);
		i++;
	}
	ft_free_double(paths);
	ft_free_double(str);
	ft_free(&str2);
}

int	exec_normal(t_cmd *cmd, t_env *env)
{
	int		*fd;

	if (is_path(cmd->cmd))
		return (exec_normal2(cmd, env));
	fd = malloc(sizeof(int) * 2);
	change_stdin_stdout(cmd->files, fd);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	search_for_path_and_exec(cmd, env);
	free(fd);
	put_error("command not found", cmd->cmd);
	return (127);
}


int	pipe_count(t_cmd *tmp)
{
	int		i;
	t_cmd	*command;

	command = tmp;
	i = 0;
	command = command->pipe;
	while (command)
	{
		command = command->next;
		i++;
	}
	return (i);
}

int	exec_child(int var, int *fd, t_cmd *cmd, t_env *env)
{
	int	pid;
	int	one;

	pid = fork();
	if (pid == 0)
	{
		if (var == 0)
		{
			dup2(fd[1], 1);
			close(fd[1]);
			close(fd[0]);
		}
		if (var != 0 && var != -1)
		{
			dup2(var, 0);
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			close(var);
		}
		if (var == -1)
		{
			dup2(fd[0], 0);
			close(fd[0]);
		}
		if (cmd->cmd && is_builtin(cmd->cmd))
		{
			one = create_files(cmd->files);
			if (one != 0)
				exit(one);
			exit(exec_builtin(cmd, env));
		}
		else if (cmd->cmd && !is_builtin(cmd->cmd) && !create_files(cmd->files))
		{
			one = create_files(cmd->files);
			if (one != 0)
				exit(one);
			exit(exec_normal(cmd, env));
		}
		else if (cmd->cmd == NULL)
			exit(create_files(cmd->files));
	}
	return (pid);
}

int	exec_pipe(t_cmd *cmd, t_env *env)
{
	int	ret;
	int	fd[2];
	int	i;
	int	pcount;
	int	inout;
	int	pid;

	i = 0;
	inout = 0;
	pcount = pipe_count(cmd);
	while (i < pcount)
	{
		pipe(fd);
		pid = exec_child(inout, fd, cmd, env);
		close(fd[1]);
		if (i != 0)
			close(inout);
		inout = fd[0];
		if (i == 0)
			cmd = cmd->pipe;
		else
			cmd = cmd->next;
		i++;
	}
	pid = exec_child(-1, fd, cmd, env);
	close(fd[0]);
	waitpid(pid, &ret, 0);
	while (--pcount >= 0)
		wait(NULL);
	return (return_value(ret));
}

int	execute(t_cmd *cmds, t_env *env)
{
	int	ret;
	int	status;
	int	pid;

	ret = 0;
	while (cmds != NULL)
	{
		if (cmds->pipe)
			ret = exec_pipe(cmds, env);
		else if (cmds->cmd && is_builtin(cmds->cmd))
		{
			if (create_files(cmds->files) == 0)
				ret = exec_builtin(cmds, env);
		}
		else if (cmds->cmd && !is_builtin(cmds->cmd))
		{
			if (create_files(cmds->files) == 0)
			{
				pid = fork();
				if (pid == 0)
					exit(exec_normal(cmds, env));
				waitpid(pid, &status, 0);
				ret = return_value(status);
			}
		}
		else if (cmds->cmd == NULL)
			ret = create_files(cmds->files);
		cmds = cmds->next;
	}
	ft_putstr_fd("\033[38;5;6m", 1);
	ft_putstr_fd(ft_itoa(ret), 1);
	return (ret);
}
