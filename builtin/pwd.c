/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 21:02:53 by ynoam             #+#    #+#             */
/*   Updated: 2021/03/31 18:46:27 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int		pwd(void)
{
	char *path;

	if ((path = getcwd(NULL, 0)) == NULL)
	{
		put_error(strerror(errno), "");
		return (1);
	}
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	free(path);
	return (0);
}
