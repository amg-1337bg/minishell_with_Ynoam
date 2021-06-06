/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:30:36 by ynoam             #+#    #+#             */
/*   Updated: 2021/05/24 19:42:11by ybamghoug        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	wait_for_last_child(int *fd, int pcount, t_cmd *cmd, t_env *env)
{
	int	status;
	int	pid;

	clean_replace(cmd, env, 0);
	change_cmd_args(cmd);
	pid = exec_child(-1, fd, cmd, env);
	close(fd[0]);
	waitpid(pid, &status, 0);
	while (--pcount >= 0)
		wait(NULL);
	return (return_value(status));
}

void	change_cmd_args(t_cmd *cmd)
{
	t_args	*tmp;

	if (cmd->cmd != NULL && cmd->cmd[0] == 0)
	{
		free(cmd->cmd);
		cmd->cmd = NULL;
		while (cmd->args && cmd->args->arg && cmd->args->arg[0] == 0)
		{
			tmp = cmd->args;
			cmd->args = cmd->args->next;
			free(tmp->arg);
			free(tmp);
		}
		if (cmd->args && cmd->args->arg)
		{
			tmp = cmd->args;
			cmd->cmd = cmd->args->arg;
			cmd->args = cmd->args->next;
			free(tmp);
		}
	}
}

int	exec_pipe(t_cmd *cmd, t_env *env)
{
	int	fd[2];
	int	i;
	int	pcount;
	int	in;
	int	pid;

	i = 0;
	in = 0;
	pcount = pipe_count(cmd);
	while (i < pcount)
	{
		pipe(fd);
		clean_replace(cmd->pipe, env, 0);
		change_cmd_args(cmd);
		exec_child(in, fd, cmd, env);
		close(fd[1]);
		if (i != 0)
			close(in);
		in = fd[0];
		if (i++ == 0)
			cmd = cmd->pipe;
		else
			cmd = cmd->next;
	}
	return (wait_for_last_child(fd, pcount, cmd, env));
}

int	execute(t_cmd *cmds, t_env *env, int cmd_return)
{
	int	ret;
	int	status;
	int	pid;

	while (cmds != NULL)
	{
		clean_replace(cmds, env, cmd_return);
		change_cmd_args(cmds);
		if (!(cmds->pipe))
			ret = create_files(cmds->files);
		if (!(cmds->pipe) && cmds->cmd && is_builtin(cmds->cmd) && !ret)
			ret = exec_builtin(cmds, env);
		else if (!(cmds->pipe) && cmds->cmd && !is_builtin(cmds->cmd) && !ret)
		{
			if (fork() == 0)
				exit(exec_normal(cmds, env));
			wait(&status);
			ret = return_value(status);
		}
		if (cmds->pipe)
			ret = exec_pipe(cmds, env);
		cmds = cmds->next;
	}
	return (ret);
}
