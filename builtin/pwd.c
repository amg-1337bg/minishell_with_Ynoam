/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 21:02:53 by ynoam             #+#    #+#             */
/*   Updated: 2021/05/29 17:12:41 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	pwd(int *fd)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		put_error(strerror(errno), "pwd");
		return (1);
	}
	ft_putstr_fd(path, fd[1]);
	ft_putstr_fd("\n", fd[1]);
	free(path);
	return (0);
}
