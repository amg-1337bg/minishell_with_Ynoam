/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoam <ynoam@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 12:09:53 by ynoam             #+#    #+#             */
/*   Updated: 2021/04/06 18:37:53 by ynoam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	cd2(t_env *env, char *hna)
{
	t_env *pwd;
	t_env *oldpwd;

	pwd = search_env_for_node(env, "PWD");
	if (pwd)
		mdf_env(env, "PWD", getcwd(NULL, 0));
	oldpwd = search_env_for_node(env, "OLDPWD");
	if (oldpwd && oldpwd->value == NULL)
		mdf_env(env, "OLDPWD", ft_strdup(""));
	else if (oldpwd && oldpwd->value != NULL)
		mdf_env(env, "OLDPWD", hna);
	else
		free(hna);
}

int		cd(t_env *env, char **path)
{
	char	*hna;
	t_env	*pwd;

	hna = getcwd(NULL, 0);
	if (path && !chdir(path[0]))
	{
		cd2(env, hna);
		return (0);
	}
	else if (!path) // cd only
		if ((pwd = search_env_for_node(env, "HOME")) == NULL || pwd->value == NULL)
		{
			free(hna);
			put_error("HOME not set", "cd");
			return (1);
		}
		else
			if (!chdir(pwd->value))
			{
				cd2(env, hna);
				return (0);
			}
	free(hna);
	put_error(strerror(errno), "cd");
	return (1);
}