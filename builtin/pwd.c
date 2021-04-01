/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 21:02:53 by ynoam             #+#    #+#             */
/*   Updated: 2021/04/01 16:17:33 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int		pwd(int	*fd)
{
	char *path;

	if ((path = getcwd(NULL, 0)) == NULL)
	{
		put_error(strerror(errno), "pwd");
		return (1);
	}
	ft_putstr_fd(path, fd[1]);
	ft_putstr_fd("\n", fd[1]);
	free(path);
	if (fd[0] != 0)
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
	return (0);
}
