/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:22:11 by ynoam             #+#    #+#             */
/*   Updated: 2021/04/07 19:11:26 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"
// export PWD OLDPWD 
// env | grep PWD
// PWD /

void	print(t_env *head, int *fd)
{
	while (head)
	{
		if (head->key)
		{
			ft_putstr_fd("declare -x ", fd[1]);
			ft_putstr_fd(head->key, fd[1]);
			if (head->value)
			{
				ft_putstr_fd("=", fd[1]);
				ft_putstr_fd("\"", fd[1]);
				ft_putstr_fd(head->value, fd[1]);
				ft_putstr_fd("\"", fd[1]);
				ft_putstr_fd("\n", fd[1]);
			}
			else
				ft_putstr_fd("\n", fd[1]);
		}
		head = head->next;
	}
}

int		export(t_env *head, char *argv[], int *fd)
{
	int		i;
	char	*join;
	char	*join2;

	if (argv)
		while (*argv)
		{
			i = 0;
			if ((ft_isalpha(*argv[i]) || *argv[i] == '_') && ++i)
				while (ft_isalnum((*argv)[i]) || (*argv)[i] == '_')
					i++;
			if ((*argv)[i] != '=' && (*argv)[i] != 0)
			{
				join =  ft_strjoin(*argv, "'");
				join2 = ft_strjoin("export: `", join);
				put_error("not a valid identifier", join2);
				ft_free(&join);
				ft_free(&join2);
			}
			else if ((*argv)[i] == '=' || (*argv)[i] == 0)
			{
				if ((*argv)[i] == 0)
					crt_env(head, ft_strdup(*argv), NULL);
				else
					crt_env(head, ft_substr(*argv, 0, i), ft_strdup(&((*argv)[i + 1])));
			}
			argv++;
		}
	else
		print(head, fd);
	return (0);
}
