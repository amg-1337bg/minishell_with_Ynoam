/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:30:36 by ynoam             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/05/26 09:43:54 by bamghoug         ###   ########.fr       */
=======
/*   Updated: 2021/05/24 19:42:11by ybamghoug        ###   ########.fr       */
>>>>>>> f0f238fe2a61d17ac00bbf4f0e2b3993b2058f04
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
<<<<<<< HEAD
		if (cmd->args)
=======
		free(cmd->cmd);
		cmd->cmd = NULL;
		while (cmd->args && cmd->args->arg && cmd->args->arg[0] == 0)
>>>>>>> f0f238fe2a61d17ac00bbf4f0e2b3993b2058f04
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
	int	inout;
	int	pid;

	i = 0;
	inout = 0;
	pcount = pipe_count(cmd);
	while (i < pcount)
	{
		pipe(fd);
		clean_replace(cmd, env, 0);
		change_cmd_args(cmd);
		exec_child(inout, fd, cmd, env);
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
