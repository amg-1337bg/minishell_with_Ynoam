/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 13:30:36 by ynoam             #+#    #+#             */
/*   Updated: 2021/05/24 13:10:49 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	wait_for_last_child(int *fd, int pcount, t_cmd *cmd, t_env *env)
{
	int	status;
	int	pid;

	pid = exec_child(-1, fd, cmd, env);
	close(fd[0]);
	waitpid(pid, &status, 0);
	while (--pcount >= 0)
		wait(NULL);
	return (return_value(status));
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
	ft_putstr_fd(ft_itoa(ret), 1);
	return (ret);
}
