/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 08:55:12 by bamghoug          #+#    #+#             */
/*   Updated: 2021/06/07 15:56:05 by bamghoug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_env	**s_env, t_cmd	**s_cmd, int argc, char **argv)
{
	*s_env = NULL;
	*s_cmd = NULL;
	argc = 0;
	argv = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*s_env;
	t_cmd	*s_cmd;
	int		cmd_return;
	t_line	*h_line[3];

	init(&s_env, &s_cmd, argc, argv);
	cmd_return = 0;
	getenvp(&s_env, envp);
	changenvp(s_env);
	tgetent(0, getenv("TERM"));
	h_line[0] = NULL;
	h_line[1] = NULL;
	h_line[2] = NULL;
	while (1)
	{
		line = get_line(h_line, &cmd_return);
		if (get_cmd(&s_cmd, line, &cmd_return) == 0)
			cmd_return = execute(s_cmd, s_env, cmd_return);
		free_cmd(&s_cmd);
		free(line);
	}
	return (cmd_return);
}
